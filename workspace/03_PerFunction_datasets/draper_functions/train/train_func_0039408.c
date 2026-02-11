test_MakeRefs()
{
  OBStereo::Refs refs = OBStereo::MakeRefs(1, 3, 5);
  OB_ASSERT( refs.size() == 3 );
  OB_ASSERT( refs[0] == 1 );
  OB_ASSERT( refs[1] == 3 );
  OB_ASSERT( refs[2] == 5 );

  refs = OBStereo::MakeRefs(1, 3, 5, 7);
  OB_ASSERT( refs.size() == 4 );
  OB_ASSERT( refs[0] == 1 );
  OB_ASSERT( refs[1] == 3 );
  OB_ASSERT( refs[2] == 5 );
  OB_ASSERT( refs[3] == 7 );
}
