nxtnet_scan(nxtnet_cli_t *cli) {
  size_t i;
  struct nxtnet_proto_list_sc *list;
  struct nxtnet_proto_list_nxts *nxt;


  list = nxtnet_cli_list(cli);
  if (list!=NULL) {
    for (i=0;i<list->num_items;i++) {
      nxt = list->nxts+i;
      printf("%d:\t%s\t%s\t%02X:%02X:%02X:%02X:%02X:%02X\n",nxt->handle, nxt->name,
                                                           nxt->is_bt?"Bluetooth":"USB",
                                                           nxt->id[0],nxt->id[1],nxt->id[2],
                                                           nxt->id[3],nxt->id[4],nxt->id[5]);
    }
  }
}
