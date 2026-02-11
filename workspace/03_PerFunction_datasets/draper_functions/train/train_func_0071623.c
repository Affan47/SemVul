pnt_comp_rand(node g1, node g2){
    if ((pnt_is_point(g1)!=TRUE)||(pnt_is_point(g2)!=TRUE)){
    bad_error("Non-PNT nodes in pnt_comp_rand()");
  }
  if (rand_int(0,1)==0) return -1;
  else return 1;
}
