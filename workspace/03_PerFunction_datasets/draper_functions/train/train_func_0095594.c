main(int argc,char *argv[])
{

  std::ios::sync_with_stdio(false);

  if (argc != 1)
    {
      cout << "Usage: data" << endl;
      cout << " Unit tests for Open Babel data tables " << endl;
      return(-1);
    }

  cout << "# Unit tests for data tables \n";


  cout << "1..2\n";

  cout << "ok 1\n";

  double mass = etab.GetMass(2);
  if ( fabs(mass - 4.0026 ) < 2e-3 )
    cout << "ok 2\n";
  else
    cout << "not ok 2\n";

  return(0);
}
