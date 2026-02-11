test_report( int nerrors, const H5std_string& testname )
{
   if (nerrors)
   {
      nerrors = MAX(1, nerrors);
	if (1 == nerrors)
	    cerr << "***** " << nerrors << testname
					<< " TEST FAILED! *****" << endl;
	else
	    cerr << "***** " << nerrors << testname
					<< " TESTS FAILED! *****" << endl;
      return 1;
   }
   else
   {
      cerr << "All" << testname << " tests passed." << endl;
      return 0;
   }
}
