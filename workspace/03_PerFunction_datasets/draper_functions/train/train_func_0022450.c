smilestest(int argc, char* argv[])
{
  int defaultchoice = 1;

  int choice = defaultchoice;

  if (argc > 1) {
    if(sscanf(argv[1], "%d", &choice) != 1) {
      printf("Couldn't parse that input as a number\n");
      return -1;
    }
  }


  #ifdef FORMATDIR
    char env[BUFF_SIZE];
    snprintf(env, BUFF_SIZE, "BABEL_LIBDIR=%s", FORMATDIR);
    putenv(env);
  #endif

  switch(choice) {
  case 1:
    testTetrahedralStereo1();

    genericSmilesCanonicalTest("C[C@H](O)N");
    genericSmilesCanonicalTest("Cl[C@@](CCl)(I)Br");

    genericSmilesCanonicalTest("Cl/C=C/F");
    break;
  case 2:

    genericSmilesCanonicalTest("F[Po](Cl)(Br)I");
    genericSmilesCanonicalTest("F[Po@SP1](Cl)(Br)I");
    genericSmilesCanonicalTest("F[Po@SP2](Br)(Cl)I");
    genericSmilesCanonicalTest("F[Po@SP3](Cl)(I)Br");
    break;
  case 3:

    genericSmilesCanonicalTest("CCC[C@@H](O)CC\\C=C\\C=C\\C#CC#C\\C=C\\CO");
    genericSmilesCanonicalTest("OC[C@@H](O1)[C@@H](O)[C@H](O)[C@@H](O)[C@@H](O)1");
    genericSmilesCanonicalTest("OC[C@@H](O1)[C@@H](O)[C@H](O)[C@@H]2[C@@H]1c3c(O)c(OC)c(O)cc3C(=O)O2");
    genericSmilesCanonicalTest("CC(=O)OCCC(/C)=C\\C[C@H](C(C)=C)CCC=C");
    genericSmilesCanonicalTest("CC[C@H](O1)CC[C@@]12CCCO2");
    genericSmilesCanonicalTest("CN1CCC[C@H]1c2cccnc2");
    genericSmilesCanonicalTest("CC(C)[C@@]12C[C@@H]1[C@@H](C)C(=O)C2");
    genericSmilesCanonicalTest("CC(C)[C@H]1CC[C@]([C@@H]2[C@@H]1C=C(COC2=O)C(=O)O)(CCl)O");
    genericSmilesCanonicalTest("C(CS[14CH2][14C@@H]1[14C@H]([14C@H]([14CH](O1)O)O)O)[C@@H](C(=O)O)N");
    genericSmilesCanonicalTest("CCC[C@@H]1C[C@H](N(C1)C)C(=O)NC([C@@H]2[C@@H]([C@@H]([C@H]([C@H](O2)SC)OP(=O)(O)O)O)O)C(C)Cl");
    break;


  default:
    cout << "Test number " << choice << " does not exist!\n";
    return -1;
  }

  return 0;
}
