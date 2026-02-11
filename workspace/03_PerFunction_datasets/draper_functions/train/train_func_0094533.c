free_Pring(Pring R)
 {
 int i;
 mem_free(R->def);
 for (i=0;i<R->n;i++){ mem_free(R->vars[i]);}
 mem_free( (char *) R->vars);
 mem_free( R);
 return 0;
 }
