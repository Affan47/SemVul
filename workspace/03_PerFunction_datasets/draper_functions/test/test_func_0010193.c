print_var(Var* v) {
  fprintf(outfile, "%s", v->name);
  if(v->idxs) {
    ExpListNode* idx = v->idxs;
    while(idx) {
      fprintf(outfile, "[");
      print_exp(idx->exp);
      fprintf(outfile, "]");
      idx = idx->next;
    }
  }
}
