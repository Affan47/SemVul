clearcache(node *n, int depth, int clearto) {
   if (!marked(n)) {
      mark(n) ;
      if (depth > 3) {
         depth-- ;
         poller->poll() ;
         clearcache(n->nw, depth, clearto) ;
         clearcache(n->ne, depth, clearto) ;
         clearcache(n->sw, depth, clearto) ;
         clearcache(n->se, depth, clearto) ;
         if (n->res)
            clearcache(n->res, depth, clearto) ;
      }
      if (depth >= clearto)
         n->res = 0 ;
   }
}
