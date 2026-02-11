search_ancestors( lListElem *ep,
                  char *name,
                  ancestors_t *ancestors,
                  int depth )
{
   lListElem *cep, *fep;
   static int sn_children_pos = -1;
   static int sn_name_pos = -1;

   DENTER(TOP_LAYER, "search_named_node");

   if (!ep || !name) {
      DEXIT;
      return NULL;
   }

   if (sn_name_pos == -1) {
      sn_children_pos = lGetPosViaElem(ep, STN_children, SGE_NO_ABORT);
      sn_name_pos = lGetPosViaElem(ep, STN_name, SGE_NO_ABORT);
   }
   if (strcmp(lGetPosString(ep, sn_name_pos), name) == 0) {
      ancestors->depth = depth;
      ancestors->nodes = (lListElem **)malloc(depth * sizeof(lListElem *));
      ancestors->nodes[depth-1] = ep;
      DEXIT;
      return ep;
   }

   for_each(cep, lGetPosList(ep, sn_children_pos)) {
      if ((fep = search_ancestors(cep, name, ancestors, depth+1))) {
         ancestors->nodes[depth-1] = ep;
         DEXIT;
         return fep;
      }
   }

   DEXIT;
   return NULL;
}
