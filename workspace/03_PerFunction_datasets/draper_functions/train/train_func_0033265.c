main(int argc, char *argv[])
{
    if (argc < 2)
    {
      fprintf(stderr, "%s\n\nusage: readoviw <dicomfile> [<dicomfile>...]\n",
      rcsid);
      return 0;
    }


    if (!dcmDataDict.isDictionaryLoaded())
    {
      fprintf(stderr, "Warning: no data dictionary loaded, check environment variable: %s\n",
        DCM_DICT_ENVIRONMENT_VARIABLE);
      return 0;
    }

    OFCondition cond = EC_Normal;
    for (int count=1; count<argc; count++)
    {
      if (count==1) printf("\\");
      DcmFileFormat dfile;

      cond = dfile.loadFile(argv[count]);

      if (cond.bad())
      {
          fprintf(stderr, "readoviw: error: %s: reading file: %s\n", dfile.error().text(), argv[count]);
      }
      else
      {
        DcmDataset *dataset = dfile.getDataset();
        if (dataset)
        {
          printStringElement(*dataset, DCM_AccessionNumber);
          printf("\\");
          printStringElement(*dataset, DCM_PatientName);
          printf("\\");
          printStringElement(*dataset, DCM_RequestedProcedureDescription);
          printf("\\");
        } else printf("\\\\\\");
      }
    }
}
