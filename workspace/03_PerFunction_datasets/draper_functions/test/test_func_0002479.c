math(int argc, char* argv[])
{
  int defaultchoice = 1;

  int choice = defaultchoice;

  if (argc > 1) {
    if(sscanf(argv[1], "%d", &choice) != 1) {
      printf("Couldn't parse that input as a number\n");
      return -1;
    }
  }

  cout << "# math: repeating each test " << REPEAT << " times" << endl;

  randomizer.TimeSeed();

  cout << "# Testing MMFF94 Force Field..." << endl;
  switch(choice) {
  case 1:
    TEST( testBasics_vector3 );
    TEST( testBasics_matrix3x3 );
    break;
  case 2:
    TEST( testArithmeticOperators );
    TEST( testDistancesAnglesOrthogonality );
    break;
  case 3:
    TEST( testInversion );
    break;
  case 4:
    TEST( testEigenvalues );
    TEST( testEigenvectors );
    break;
  default:
    cout << "Test number " << choice << " does not exist!\n";
    return -1;
  }

  cout << "1.." << testCount << endl;

  if( failedCount == 0 ) cout << "# math: all tests are successful" << endl;
  else cout << "# math: " << failedCount << " out of "
            << testCount << " tests failed." << endl;
  return 0;
}
