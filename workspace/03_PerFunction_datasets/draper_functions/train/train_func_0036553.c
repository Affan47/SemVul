test_equalsThisOperator()
{
  OBSquarePlanarStereo sq1(0), sq2(0);
  OBSquarePlanarStereo::Config cfg;
  cfg.center = 0;
  cfg.refs = OBStereo::MakeRefs(1, 2, 3, 4);

  sq1.SetConfig(cfg);
  sq2.SetConfig(cfg);
  OB_ASSERT( sq1 == sq2 );

  cfg.shape = OBStereo::ShapeZ;
  sq2.SetConfig(cfg);
  OB_ASSERT( sq1 != sq2 );

  OBStereo::Permutate(cfg.refs, 0, 1);
  sq2.SetConfig(cfg);
  OB_ASSERT( sq1 == sq2 );
}
