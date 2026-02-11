checkfile(const char *filename)
{
    DcmFileFormat *dfile = new DcmFileFormat();
    if (dfile == NULL)
    {
      OFLOG_ERROR(dcmpschkLogger, "out of memory.");
      return -1;
    }

    OFCondition cond = dfile->loadFile(filename);
    if (! cond.good())
    {
      OFLOG_ERROR(dcmpschkLogger, cond.text() << " reading file: " << filename);
      delete dfile;
      return -1;
    }

    int numberOfErrors = 0;
    OFBool test_passed = OFTrue;

    DcmDataset *DataSet = dfile->getDataset();
    DcmMetaInfo *MetaInfo = dfile->getMetaInfo();

    OFLOG_INFO(dcmpschkLogger, "=========================================================");
    OFLOG_WARN(dcmpschkLogger, "Testing: " << filename);
    OFLOG_INFO(dcmpschkLogger, "=========================================================");

    if (MetaInfo)
    {
      OFLOG_INFO(dcmpschkLogger, "---------------------------------------------------------" << OFendl
            << "Pass 1 - Inconsistencies between Meta-header and Data Set" << OFendl
            << "---------------------------------------------------------");
      numberOfErrors += dcmchkMetaHeader(MetaInfo, DataSet);
    }

    OFLOG_INFO(dcmpschkLogger, "-------------------------------------------------------------" << OFendl
          << "Pass 2 - Inconsistencies between Data Dictionary and Data Set" << OFendl
          << "-------------------------------------------------------------");

    dcmchk(opt_filename, ERM_autoDetect, EXS_Unknown,
          OFFalse , OFTrue ,
          numberOfErrors);

    OFLOG_INFO(dcmpschkLogger, "-------------------------------------------------------------" << OFendl
          << "Pass 3 - Semantic Check of Presentation State Object         " << OFendl
          << "-------------------------------------------------------------");

    DcmUniqueIdentifier sopclassuid(DCM_SOPClassUID);
    DcmStack stack;
    if (EC_Normal == DataSet->search(DCM_SOPClassUID, stack, ESM_fromHere, OFFalse))
    {
      sopclassuid = *((DcmUniqueIdentifier *)(stack.top()));
    }
    OFString aString;
    sopclassuid.getOFString(aString,0);
    if (aString == UID_GrayscaleSoftcopyPresentationStateStorage)
    {
      DcmPresentationState pState;
      if (pState.read(*DataSet).bad())
      {
        test_passed = OFFalse;
      }
    } else {
      OFLOG_INFO(dcmpschkLogger, "Not a Grayscale Softcopy Presentation State, skipping pass 3.");
    }
    if (numberOfErrors > 0) test_passed = OFFalse;

    if (test_passed) OFLOG_WARN(dcmpschkLogger, "Test passed.");
    else OFLOG_WARN(dcmpschkLogger, "Test failed - one or more errors.");

    if (dfile) delete dfile;
    return numberOfErrors;
}
