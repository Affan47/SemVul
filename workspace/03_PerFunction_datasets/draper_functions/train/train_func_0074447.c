find_node(node *nw, node *ne, node *sw, node *se) {
   node *p ;
   g_uintptr_t h = node_hash(nw,ne,sw,se) ;
   node *pred = 0 ;
   h = h % hashprime ;
   for (p=hashtab[h]; p; p = p->next) {
      if (nw == p->nw && ne == p->ne && sw == p->sw && se == p->se) {
         if (pred) {
            pred->next = p->next ;
            p->next = hashtab[h] ;
            hashtab[h] = p ;
         }
         return save(p) ;
      }
      pred = p ;
   }
   p = newnode() ;
   p->nw = nw ;
   p->ne = ne ;
   p->sw = sw ;
   p->se = se ;
   p->res = 0 ;
   p->next = hashtab[h] ;
   hashtab[h] = p ;
   hashpop++ ;
   if (hashpop > hashlimit)
      resize() ;
   return save(p) ;
}
