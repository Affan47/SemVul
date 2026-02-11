Gen_set_lval(Gen_node g,Gen_node g1){
  if (g==0) return 0;
  else return (g->Genval.lval=g1);
}
