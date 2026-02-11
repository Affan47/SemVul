geme_mulT2ST2S_T4S_ikjl( FMField *t4, FMField *t21, FMField *t22 )
{
  int32 iqp, ir, ic, ii, ij, ik, il, s1, s2;
  int32 sym = t4->nRow, dim;
  float64 *pt4, *pt21, *pt22;
  int32 *t2i = 0, *t2j = 0, *t4s = 0;

  dim = sym2dim( sym );

  switch (dim) {
  case 2:
    t2i = t2i2D;
    t2j = t2j2D;
    t4s = t4s2D;
    break;
  case 3:
    t2i = t2i3D;
    t2j = t2j3D;
    t4s = t4s3D;
    break;
  default:
    errput( ErrHead "ERR_Switch\n" );
  }

  for (iqp = 0; iqp < t4->nLev; iqp++) {
    pt4 = FMF_PtrLevel( t4, iqp );
    pt21 = FMF_PtrLevel( t21, iqp );
    pt22 = FMF_PtrLevel( t22, iqp );
    for (ir = 0; ir < sym; ir++) {
      for (ic = 0; ic < sym; ic++) {
	ii = t2i[ir];
	ij = t2j[ir];
	ik = t2i[ic];
	il = t2j[ic];
	s1 = t4s[dim*ii+ik];
	s2 = t4s[dim*ij+il];
	pt4[sym*ir+ic] = pt21[s1] * pt22[s2];
      }
    }
  }

  return( RET_OK );
}
