bond(int argc, char* argv[])
{
  int defaultchoice = 1;

  int choice = defaultchoice;

  if (argc > 1) {
    if(sscanf(argv[1], "%d", &choice) != 1) {
      printf("Couldn't parse that input as a number\n");
      return -1;
    }
  }

  cout << "# Unit tests for OBBond \n";

  OBAtom emptyAtom, begin1, end1;
  OBBond emptyBond, bond1;

  switch(choice) {
  case 1:

    bond1.SetBegin(&begin1);
    bond1.SetEnd(&end1);
    cout << "ok 3\n";
    break;
  default:
    cout << "Test number " << choice << " does not exist!\n";
    return -1;
  }

  return(0);
}
