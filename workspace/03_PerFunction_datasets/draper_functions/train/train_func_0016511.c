stereotest(int argc, char* argv[])
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
    test_MakeRefs();
    break;
  case 2:
    test_ContainsSameRefs();
    break;
  case 3:
    test_NumInversions();
    break;
  case 4:
    test_Permutate();
    break;
  case 5:
    test_Permutated();
    break;
  case 6:
    test_StereoPerception();
    break;
  default:
    cout << "Test number " << choice << " does not exist!\n";
    return -1;
  }

  return 0;
}
