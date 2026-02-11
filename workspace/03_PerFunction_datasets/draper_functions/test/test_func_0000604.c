first_poly_no(polyominoesstruct *sp)
{
  int poly_no;

  poly_no = 0;
  while(poly_no<sp->nr_polyominoes && sp->polyomino[poly_no].attached)
    poly_no++;
  return poly_no;
}
