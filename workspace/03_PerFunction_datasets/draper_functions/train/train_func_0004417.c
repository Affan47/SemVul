mpoa_resolution_reply( uint8_t * buff ){
  int pos = 0;
  struct k_message msg;
  struct extension_values values;
  struct nhrp_common_h *common;
  struct nhrp_cie *cie;
  struct nhrp_fixed_h *fixed = (struct nhrp_fixed_h*)buff;
  memset(&values, 0, sizeof(struct extension_values));
  memset(&msg,0,sizeof(struct k_message));
  pos += sizeof(struct nhrp_fixed_h);
  common = (struct nhrp_common_h*)(buff + pos);
  if(!check_incoming(ntohl(common->request_ID),MPOA_RESOLUTION_REQUEST))
    return -1;
  pos += sizeof(struct nhrp_common_h);
  cie = (struct nhrp_cie*)(buff + pos);
  if(cie->code){
    print_cie_code(cie->code);
    return -1;
  }
  msg.content.in_info.holding_time = ntohs(cie->holding_time);
  if(fixed->ar_extoff)
    pos += parse_extensions(buff + ntohs(fixed->ar_extoff), &values);
  if (values.egress_cache_tag_ext_present == 0) {
          printf("mpcd: p_recogn.c: warning: ");
          printf("received MPOA Resolution Reply ");
          printf("with no Egress Cache Tag Extension\n");
  }
  if(values.tag_present && values.tag == 0) {
          printf("mpcd: p_recogn.c: warning: ");
          printf("received MPOA Resolution Reply ");
          printf("with Egress Cache Tag Extension where tag == 0\n");
          values.tag_present = 0;
  }
  if(values.tag_present){
    msg.content.in_info.tag = values.tag;
  }
  msg.type = MPOA_RES_REPLY_RCVD;
  msg.content.in_info.in_dst_ip  = common->dst_protocol_address;
  memcpy(msg.content.in_info.eg_MPC_ATM_addr,cie->cli_nbma_address,ATM_ESA_LEN);
  memcpy(msg.MPS_ctrl,mpc_control.MPS_CTRL_ATM_ADDR, ATM_ESA_LEN);
  if(values.service_category_present)
    msg.qos.txtp.traffic_class = service_category_to_traff_class(values.service_category);
  else
    msg.qos.txtp.traffic_class = ATM_UBR;
  send_to_kernel(&msg);
  keep_alive_sm_running = 1;
  return MPOA_RESOLUTION_REPLY;
}
