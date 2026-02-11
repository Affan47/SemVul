test_alignMolWithSym(){
  OBConversion conv;
  OB_REQUIRE( conv.SetInFormat("smi") );

  OBMol mol;
  OB_REQUIRE( conv.ReadString(&mol, "ClC(=O)Cl") );

  OBBuilder builder;
  OB_REQUIRE( builder.Build(mol) );


  OBAtom *patom = mol.GetAtom(1);
  patom->SetVector( patom->GetVector() + vector3(.1, .1, .1) );

  OBMol mol_b = mol;


  OBAlign align = OBAlign(mol, mol_b, true, true);
  align.Align();
  double rmsd = align.GetRMSD();
  OB_ASSERT( fabs(rmsd) < 1.0E-6 );


  vector<int> a(4);
  a[0] = 4; a[1] = 2; a[2] = 3; a[3] = 1;
  mol_b.RenumberAtoms(a);
  align.SetTargetMol(mol_b);
  align.Align();
  rmsd = align.GetRMSD();
  OB_ASSERT( fabs(rmsd) < 1.0E-6 );


  align = OBAlign(mol, mol_b, true, false);
  align.Align();
  rmsd = align.GetRMSD();
  OB_ASSERT( fabs(rmsd) > 1.0E-2 );

}
