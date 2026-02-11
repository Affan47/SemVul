zeroghnode(int depth) {
   while (depth >= nzeros) {
      int nnzeros = 2 * nzeros + 10 ;
      zeroghnodea = (ghnode **)realloc(zeroghnodea,
                                          nnzeros * sizeof(ghnode *)) ;
      if (zeroghnodea == 0)
        lifefatal("Out of memory (2).") ;
      alloced += (nnzeros - nzeros) * sizeof(ghnode *) ;
      while (nzeros < nnzeros)
         zeroghnodea[nzeros++] = 0 ;
   }
   if (zeroghnodea[depth] == 0) {
      if (depth == 0) {
         zeroghnodea[depth] = (ghnode *)find_ghleaf(0, 0, 0, 0) ;
      } else {
         ghnode *z = zeroghnode(depth-1) ;
         zeroghnodea[depth] = find_ghnode(z, z, z, z) ;
      }
   }
   return zeroghnodea[depth] ;
}
