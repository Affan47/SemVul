find_end_tag(HSCPRC * hp, STRPTR tagname) {
   DLNODE *nd = find_dlnode_bw(dll_last(hp->container_stack),
         (APTR) tagname, cmp_strtag);

   return (HSCTAG*) ((NULL != nd) ? dln_data(nd) : NULL);
}
