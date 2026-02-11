nxtnet_srv_list(nxtnet_srv_t *srv, struct nxtnet_proto_packet *packet) {
  struct nxtnet_proto_list_sc *list = (struct nxtnet_proto_list_sc*)packet->data;

  nxtnet_srv_log(srv,"Listing NXTs\n");

  list->num_items = 0;
  packer_buf = list;

  if (srv->ops.list!=NULL) {
    srv->ops.list(packer_func);
    packet->error = 0;
  }
  else packet->error = NXTNET_ERROR_NOTIMPL;

  packet->cmd = NXTNET_PROTO_DIR_SC|NXTNET_PROTO_CMD_LIST;
  packet->size = sizeof(struct nxtnet_proto_packet)+sizeof(struct nxtnet_proto_list_sc)+ntohl(list->num_items)*sizeof(struct nxtnet_proto_list_nxts);
  packet->error = 0;
}
