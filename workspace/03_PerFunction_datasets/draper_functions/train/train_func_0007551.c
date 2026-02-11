testCenter()
{
  OBMol mol;
  OBSquarePlanarStereo sp(&mol);
  OBSquarePlanarStereo::Config cfg;
  cfg.center = 42;
  cfg.refs = OBStereo::MakeRefs(1, 2, 3, 4);
  sp.SetConfig(cfg);
  OB_REQUIRE( sp.GetConfig().center == 42 );
}
