test_RMSD()
{


  vector3 a(-1, -1, 0), b(1, 1, 0), c(-1, 1.1, 0), d(1, -1, 0), e(sqrt(8.) + 1, 1, 0);

  double rmsd;
  vv3 ref(2), target(2);
  ref[0] = d; ref[1] = b;


  target[0] = a; target[1] = c;
  OBAlign align(ref, target);
  align.Align();
  rmsd = align.GetRMSD();
  OB_ASSERT( fabs(rmsd - 0.05) < 1.0E-06 );
}
