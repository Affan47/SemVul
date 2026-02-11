genCodePostorderArrayVar(Absyn *node, Table *symtab, int r) {
  int actualarraysize, basetypesize;
  if(r+2>R_MAX) error("zuwenig Register in genCodePostorderArrayVar()");

  genCodePostorder(node->u.arrayVar.var, symtab, r);
  genCodePostorder(node->u.arrayVar.index, symtab, r+1);

  basetypesize = node->type_t->size;
  actualarraysize = node->u.arrayVar.var->type_t->u.arrayType.size;

  fprintf(file, "\tadd\t$%d,$%d,%d\n", r+2, 0, actualarraysize);
  fprintf(file, "\tbgeu\t$%d,$%d,_indexError\n", r+1, r+2);
  fprintf(file, "\tmul\t$%d,$%d,%d\n", r+1, r+1, basetypesize);
  fprintf(file, "\tadd\t$%d,$%d,$%d\n", r, r, r+1);
}
