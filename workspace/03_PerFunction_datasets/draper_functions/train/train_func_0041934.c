main()
{

  #ifdef FORMATDIR
    char env[BUFF_SIZE];
    snprintf(env, BUFF_SIZE, "BABEL_LIBDIR=%s", FORMATDIR);
    putenv(env);
  #endif

  genericGraphSymTest("C[C@H](O)N");
  genericGraphSymTest("Cl[C@@](CCl)(I)Br");
  genericGraphSymTest("Cl/C=C/F");
  genericGraphSymTest("CCC[C@@H](O)CC\\C=C\\C=C\\C#CC#C\\C=C\\CO");
  genericGraphSymTest("O1C=C[C@H]([C@H]1O2)c3c2cc(OC)c4c3OC(=O)C5=C4CCC(=O)5");
  genericGraphSymTest("OC[C@@H](O1)[C@@H](O)[C@H](O)[C@@H](O)[C@@H](O)1");
  genericGraphSymTest("OC[C@@H](O1)[C@@H](O)[C@H](O)[C@@H]2[C@@H]1c3c(O)c(OC)c(O)cc3C(=O)O2");
  genericGraphSymTest("CC(=O)OCCC(/C)=C\\C[C@H](C(C)=C)CCC=C");
  genericGraphSymTest("CC[C@H](O1)CC[C@@]12CCCO2");
  genericGraphSymTest("CN1CCC[C@H]1c2cccnc2");
  genericGraphSymTest("C(CS[14CH2][14C@@H]1[14C@H]([14C@H]([14CH](O1)O)O)O)[C@@H](C(=O)O)N");
  genericGraphSymTest("CCC[C@@H]1C[C@H](N(C1)C)C(=O)NC([C@@H]2[C@@H]([C@@H]([C@H]([C@H](O2)SC)OP(=O)(O)O)O)O)C(C)Cl");
  genericGraphSymTest("CC(C)[C@H]1CC[C@]([C@@H]2[C@@H]1C=C(COC2=O)C(=O)O)(CCl)O");
  genericGraphSymTest("CC(C)[C@@]12C[C@@H]1[C@@H](C)C(=O)C2");


  genericGraphSymTest("Cc1cn(c(=O)[nH]c1=O)[C@H]1C[C@@H]([C@H](O1)CNCc1ccccc1)O");

  countGraphSymClassesTest("stereo/razinger_fig3.mol", 4);
  countGraphSymClassesTest("stereo/razinger_fig7_1.mol", 5);
  countGraphSymClassesTest("stereo/razinger_fig7_2.mol", 7);
  countGraphSymClassesTest("stereo/razinger_fig7_3.mol", 7);
  countGraphSymClassesTest("stereo/razinger_fig7_4.mol", 7);
  countGraphSymClassesTest("stereo/razinger_fig7_5.mol", 5);
  countGraphSymClassesTest("stereo/razinger_fig7_6.mol", 4);
  countGraphSymClassesTest("stereo/razinger_fig7_7.mol", 7);
  countGraphSymClassesTest("stereo/razinger_fig7_8.mol", 7);
  countGraphSymClassesTest("stereo/razinger_fig7_9.mol", 10);
  countGraphSymClassesTest("stereo/razinger_fig7_10.mol", 13);
  countGraphSymClassesTest("stereo/razinger_fig7_11.mol", 9);
  countGraphSymClassesTest("stereo/razinger_fig7_12.mol", 17);
  countGraphSymClassesTest("stereo/razinger_fig7_13.mol", 4);
  countGraphSymClassesTest("stereo/razinger_fig7_14.mol", 4);
  countGraphSymClassesTest("stereo/razinger_fig7_15.mol", 5);
  countGraphSymClassesTest("stereo/razinger_fig7_16.mol", 4);
  countGraphSymClassesTest("stereo/razinger_fig7_17.mol", 5);
  countGraphSymClassesTest("stereo/razinger_fig7_18.mol", 3);
  countGraphSymClassesTest("stereo/razinger_fig7_19.mol", 6);
  countGraphSymClassesTest("stereo/razinger_fig7_20.mol", 5);
  countGraphSymClassesTest("stereo/razinger_fig7_21.mol", 7);
  countGraphSymClassesTest("stereo/razinger_fig7_22.mol", 2);
  countGraphSymClassesTest("stereo/razinger_fig7_23.mol", 4);
  countGraphSymClassesTest("stereo/razinger_fig7_24.mol", 4);
  countGraphSymClassesTest("stereo/razinger_fig7_25.mol", 4);
  countGraphSymClassesTest("stereo/razinger_fig7_26.mol", 4);
  countGraphSymClassesTest("stereo/razinger_fig7_27.mol", 8);
  countGraphSymClassesTest("stereo/razinger_fig7_28.mol", 3);
  countGraphSymClassesTest("stereo/razinger_fig7_29.mol", 6);


  countGraphSymClassesTest("stereo/razinger_fig7_48.mol", 3);
  countGraphSymClassesTest("stereo/razinger_fig7_49.mol", 11);
  countGraphSymClassesTest("stereo/razinger_fig7_50.mol", 5);
  countGraphSymClassesTest("stereo/razinger_fig7_51.mol", 7);
  countGraphSymClassesTest("stereo/razinger_fig7_52.mol", 4);


  countGraphSymClassesTest("stereo/razinger_fig7_58.mol", 5);
  countGraphSymClassesTest("stereo/razinger_fig7_59.mol", 4);
  countGraphSymClassesTest("stereo/razinger_fig7_60.mol", 7);


  countGraphSymClassesTest("stereo/razinger_fig7_64.mol", 8);


  countGraphSymClassesTest("stereo/razinger_fig7_69.mol", 2);
  cout << "end" << endl;

  return 0;
}
