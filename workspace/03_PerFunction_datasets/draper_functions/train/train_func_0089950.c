main(int argc,char **argv)
{

   OpenBabel::OBMol mol;
   OpenBabel::OBAtom* a[5];
   a[0] = mol.NewAtom(); a[0]->SetAtomicNum(6);  a[0]->SetVector(-0.013,  1.086,  0.008);
   a[1] = mol.NewAtom(); a[1]->SetAtomicNum(1);  a[1]->SetVector( 0.002, -0.004,  0.002);
   a[2] = mol.NewAtom(); a[2]->SetAtomicNum(9);  a[2]->SetVector( 1.300,  1.570, -0.002);
   a[3] = mol.NewAtom(); a[3]->SetAtomicNum(35); a[3]->SetVector(-0.964,  1.737, -1.585);
   a[4] = mol.NewAtom(); a[4]->SetAtomicNum(17); a[4]->SetVector(-0.857,  1.667,  1.491);
   OpenBabel::OBBond* b;
   for (int i(1); i < 5; ++i)
   {
      b = mol.NewBond();
      b->SetBegin(a[0]); b->SetEnd(a[i]); b->SetBondOrder(1);
   }


   test01(&mol);
   test02(&mol);
   test03(&mol);
   test04(&mol);
   test05(&mol);
   test06(&mol);
   test07(&mol);
   test08(&mol);
   test09(&mol);


   return 0;
}
