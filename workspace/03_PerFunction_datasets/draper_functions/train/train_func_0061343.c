ipmi_lanplus_build_v2x_ipmi_cmd(
								struct ipmi_intf * intf,
								struct ipmi_rq * req,
								int isRetry)
{
	struct ipmi_v2_payload v2_payload;
	struct ipmi_rq_entry * entry;


	static uint8_t curr_seq = 0;

	if( isRetry == 0 )
		curr_seq += 1;

	if (curr_seq >= 64)
		curr_seq = 0;


	if ((intf->target_addr == intf->my_addr) || (!bridgePossible))
   {
	entry = ipmi_req_add_entry(intf, req, curr_seq);
   }
   else
   {
      unsigned char backup_cmd;


   	entry = ipmi_req_add_entry(intf, req, curr_seq);

      if(entry)
      {

         backup_cmd = req->msg.cmd;
         req->msg.cmd = 0x34;
   	   entry = ipmi_req_add_entry(intf, req, curr_seq);
         req->msg.cmd = backup_cmd;
      }
   }

	if (entry == NULL)
		return NULL;


	v2_payload.payload_type                 = IPMI_PAYLOAD_TYPE_IPMI;
	v2_payload.payload_length               = req->msg.data_len + 7;
	v2_payload.payload.ipmi_request.request = req;
	v2_payload.payload.ipmi_request.rq_seq  = curr_seq;

	ipmi_lanplus_build_v2x_msg(intf,
					&v2_payload,
					&(entry->msg_len),
					&(entry->msg_data),
					curr_seq);

	return entry;
}
