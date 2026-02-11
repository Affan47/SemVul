testRefs1()
{
  OBMol mol;
  OBSquarePlanarStereo sp(&mol);
  OBSquarePlanarStereo::Config cfg;


  cfg.center = 0;
  cfg.refs = OBStereo::MakeRefs(1, 2, 3, 4);
  sp.SetConfig(cfg);

  vector<unsigned long> refs;

  refs = sp.GetConfig().refs;
  OB_REQUIRE( refs.size() == 4 );
  OB_REQUIRE( refs[0] == 1 );
  OB_REQUIRE( refs[1] == 2 );
  OB_REQUIRE( refs[2] == 3 );
  OB_REQUIRE( refs[3] == 4 );


  refs = sp.GetConfig(OBStereo::ShapeZ).refs;
  OB_REQUIRE( refs.size() == 4 );
  OB_REQUIRE( refs[0] == 1 );
  OB_REQUIRE( refs[1] == 2 );
  OB_REQUIRE( refs[2] == 4 );
  OB_REQUIRE( refs[3] == 3 );


  refs = sp.GetConfig(OBStereo::Shape4).refs;
  OB_REQUIRE( refs.size() == 4 );
  OB_REQUIRE( refs[0] == 1 );
  OB_REQUIRE( refs[1] == 3 );
  OB_REQUIRE( refs[2] == 2 );
  OB_REQUIRE( refs[3] == 4 );
}
