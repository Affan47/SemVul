host_complexes2scheduler(
lList **new_centry_list,
lListElem *host,
lList *exechost_list,
lList *centry_list
) {
   DENTER(TOP_LAYER, "host_comlexes2scheduler");

   if (!host) {
      DPRINTF(("!!missing host!!\n"));
   }

   lFreeList(new_centry_list);
   *new_centry_list = get_attribute_list(host_list_locate(exechost_list, "global"), host, NULL, centry_list);

   DRETURN(0);
}
