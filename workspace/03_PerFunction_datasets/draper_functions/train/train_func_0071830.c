xsh_the_map_lambda_order_slit_compare(const void* one,
  const void* two){

  xsh_the_arcline** a = NULL;
  xsh_the_arcline** b = NULL;
  float la, lb;
  int oa, ob;
  float sa, sb;

  a = (xsh_the_arcline**) one;
  b = (xsh_the_arcline**) two;

  la = (*a)->wavelength;
  lb = (*b)->wavelength;

  oa = (*a)->order;
  ob = (*b)->order;

  sa = (*a)->slit_position;
  sb = (*b)->slit_position;

  if ( (lb - la) > WAVELENGTH_PRECISION ){
    return -1;
  }
  else if ((lb - la) < WAVELENGTH_PRECISION ){
    return 1;
  }
  else {
    if (oa < ob) {
      return -1;
    }
    else if ( oa > ob) {
      return 1;
    }
    else{
      if (sa <= sb){
        return -1;
      }
      else{
        return 1;
      }
    }
  }
}
