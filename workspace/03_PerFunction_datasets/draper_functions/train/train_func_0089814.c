dodec_wrap(x, y, element)
      REAL x[PDIM], y[PDIM];
      WRAPTYPE element;
{
  REAL mat[PDIM][PDIM];
  int i;

  if(q_init_flag==0) init_gen();

  if(element==0)
     for(i=0;i<SDIM;i++)
        y[i] = x[i];
  else {
     convertToHyp(x, y);
     calcElem(element, mat);
     matVecMult(mat, y, y);
     for(i=0;i<SDIM;i++)
        y[i] /= y[3];
  }
}
