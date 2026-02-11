main()
{
  COUT << "Test program for LFS support in DCMTK class OFFile\n" << OFendl;


  srand(OFstatic_cast(unsigned int, time(NULL)));


  COUT << "Checking typedefs.\n"
       << "- size of offile_off_t: " << sizeof(offile_off_t);
  if (sizeof(offile_off_t) > 4) COUT << " - OK\n"; else COUT << " - too small, no LFS support\n";
  COUT << "- size of offile_fpos_t: " << sizeof(offile_fpos_t);
  if (sizeof(offile_fpos_t) > 4) COUT << " - OK\n"; else COUT << " - too small, no LFS support\n";
  if ((sizeof(offile_off_t) <= 4 || sizeof(offile_fpos_t) <= 4))
  {
    COUT << "No LFS support available. LFS test failed." << OFendl;
    return 10;
  }

  OFFile file;

  if (OFStandard::fileExists(FILENAME))
  {
    COUT << "\nData file " << FILENAME << " already exists, let's just use it." << OFendl << STD_NAMESPACE flush;
  }
  else
  {
    COUT << "\nCreating a 6 GByte data file." << OFendl << STD_NAMESPACE flush;
    if (!file.fopen(FILENAME, "w+b"))
    {
      COUT << "Error: Unable to create file " << FILENAME << ". LFS test failed." << OFendl;
      return 10;
    }

    if (! fillFile(file))
    {
      COUT << "Error: Unable to write 6 GByte of data. LFS test failed." << OFendl;
      return 10;
    }

    if (! seekFile(file))
    {
      COUT << "Error: fseek() tests unsuccessful. LFS test failed." << OFendl;
      return 10;
    }

    COUT << "Closing file." << OFendl << STD_NAMESPACE flush;

    file.fclose();
  }

  COUT << "Re-opening file in read-only mode." << OFendl << STD_NAMESPACE flush;

  if (!file.fopen(FILENAME, "rb"))
  {
    COUT << "Error: Unable to open file " << FILENAME << ". LFS test failed." << OFendl;
    return 10;
  }

  if (! seekFile(file))
  {
    COUT << "Error: fseek() tests unsuccessful. LFS test failed." << OFendl;
    return 10;
  }


  return 0;
}
