lssrtest(int argc, char* argv[])
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
    OB_ASSERT( doShuffleTestMultiFile("aromatics.smi") );
    break;
  case 2:
    OB_ASSERT( doShuffleTestMultiFile("nci.smi") );
    break;
  case 3:
    OB_ASSERT( doShuffleTestMultiFile("attype.00.smi") );
    break;
  case 4:
    OB_ASSERT( doShuffleTestMultiFile("rings/tetrahedron.mdl") );
    OB_ASSERT( doShuffleTestMultiFile("rings/cubane.mdl") );
    OB_ASSERT( doShuffleTestMultiFile("rings/cubane2.mdl") );
    OB_ASSERT( doShuffleTestMultiFile("rings/octahedron.mdl") );
    OB_ASSERT( doShuffleTestMultiFile("rings/bridged1.mdl") );
    OB_ASSERT( doShuffleTestMultiFile("rings/fullerene20.mdl") );
    OB_ASSERT( doShuffleTestMultiFile("rings/fullerene60.mdl") );
    break;
  case 5:

    OB_ASSERT( verifyLSSR("rings/tetrahedron.mdl", LSSR(LSSR::Size_Count(3, 4), LSSR::Size_Count(5, 1))) );

    OB_ASSERT( verifyLSSR("rings/cubane.mdl", LSSR(LSSR::Size_Count(4, 6), LSSR::Size_Count(6, 1))) );
    OB_ASSERT( verifyLSSR("rings/cubane2.mdl", LSSR(LSSR::Size_Count(4, 6), LSSR::Size_Count(6, 1))) );

    OB_ASSERT( verifyLSSR("rings/octahedron.mdl", LSSR(LSSR::Size_Count(3, 8))) );

    OB_ASSERT( verifyLSSR("rings/bridged1.mdl", LSSR(LSSR::Size_Count(6, 3))) );

    OB_ASSERT( verifyLSSR("rings/fullerene20.mdl", LSSR(LSSR::Size_Count(5, 12))) );

    OB_ASSERT( verifyLSSR("rings/fullerene60.mdl", LSSR(LSSR::Size_Count(5, 12), LSSR::Size_Count(6, 20))) );
    break;
  default:
    cout << "Test number " << choice << " does not exist!\n";
    return -1;
  }

  return 0;
}
