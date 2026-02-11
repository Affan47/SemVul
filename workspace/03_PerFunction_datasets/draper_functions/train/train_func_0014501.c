uniqueidtest(int argc, char* argv[])
{
  int defaultchoice = 1;

  int choice = defaultchoice;

  if (argc > 1) {
    if(sscanf(argv[1], "%d", &choice) != 1) {
      printf("Couldn't parse that input as a number\n");
      return -1;
    }
  }

  switch(choice) {
  case 1:

    testIdsNewAtom1();
    testIdsNewAtom2();
    testIdsDeleteAtom();
    testIdsAddAtom();
    break;

  case 2:

    testIdsNewBond1();
    testIdsNewBond2();
    testIdsDeleteBond();
    testIdsAddBond();
    break;

  default:
    cout << "Test number " << choice << " does not exist!\n";
    return -1;
  }

  return 0;
}
