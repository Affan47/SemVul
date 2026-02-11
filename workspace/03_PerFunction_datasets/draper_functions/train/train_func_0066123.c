get_version(const string& infilename)
{
  string dummystring;
  int version;
  ifstream headerfile(infilename.c_str());

  headerfile >> dummystring;

  if(dummystring=="V"){
    headerfile >> version ;
    cout << "version : " << version << endl;
  } else {
    cout << "pre- V.1 version" << endl;
    version=0;
  }
  headerfile.close();

  return version;
}
