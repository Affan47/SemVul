testAutomorphismMask2()
{

  cout <<  "testAutomorphismMask2" << endl;
  OBMol mol;
  OBConversion conv;

  conv.SetInFormat("sdf");
  std::ifstream ifs(GetFilename("progesterone.sdf").c_str());
  OB_REQUIRE( ifs );
  OB_REQUIRE( conv.Read(&mol, &ifs) );

  Automorphisms _aut;
  OBBitVec _frag_atoms;
  FOR_ATOMS_OF_MOL(a, mol) {
    if(!(a->IsHydrogen()))
      _frag_atoms.SetBitOn(a->GetIdx());
  }
  FindAutomorphisms((OBMol*)&mol, _aut, _frag_atoms);
  OB_ASSERT( _aut.size() == 1 );

}
