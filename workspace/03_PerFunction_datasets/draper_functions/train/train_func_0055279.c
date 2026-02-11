test_alignWithSymWithoutHydrogens() {
  OBConversion conv;
  bool success = conv.SetInFormat("smi");
  OB_REQUIRE( success );

  OBMol mol;
  success = conv.ReadString(&mol, "BrCC(Cl)(Cl)Cl");
  OB_REQUIRE( success );

  OBBuilder builder;
  OB_REQUIRE( builder.Build(mol) );
  mol.AddHydrogens();


  OBMol clone = mol;
  double ang = mol.GetTorsion(1, 2, 3, 4);
  clone.SetTorsion( clone.GetAtom(1), clone.GetAtom(2), clone.GetAtom(3), clone.GetAtom(4), (ang + 120) * DEG_TO_RAD );


  OBAlign align = OBAlign(mol, clone, true, false);
  align.Align();
  double rmsd = align.GetRMSD();
  OB_ASSERT( fabs(rmsd) > 1.2 );


  align = OBAlign(mol, clone, true, true);
  align.Align();
  rmsd = align.GetRMSD();
  OB_ASSERT( fabs(rmsd) < 0.017 );


  align = OBAlign(mol, clone, false, true);
  align.Align();
  rmsd = align.GetRMSD();
  OB_ASSERT( fabs(rmsd) < 0.019 );
}
