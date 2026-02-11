verifyAndSignStructuredReport(const char *userID, const char * , DVPSVerifyAndSignMode mode)
#endif
{
  OFCondition result = EC_IllegalCall;
  if ((pReport != NULL) && (userID != NULL))
  {
    OFString userName(getUserDICOMName(userID));
    OFString userOrg(getUserOrganization(userID));
    OFString userCV, userCSD, userCSV, userCM;
    DSRCodedEntryValue userCode(getUserCodeValue(userID, userCV), getUserCodingSchemeDesignator(userID, userCSD),
                                getUserCodingSchemeVersion(userID, userCSV), getUserCodeMeaning(userID, userCM));

    if (pReport->verifyDocument(userName, userCode, userOrg) == EC_Normal)
    {
      if ((mode == DVPSY_verifyAndSign) || (mode == DVPSY_verifyAndSign_finalize))
      {
#ifdef WITH_OPENSSL
        if (pSignatureHandler)
        {
          DcmStack stack;
          DcmItem dataset;
          if (pReport->write(dataset, &stack) == EC_Normal)
          {
            DcmAttributeTag tagList(DcmTag(0, 0) );
            if (mode == DVPSY_verifyAndSign)
            {

              tagList.putTagVal(DCM_SOPInstanceUID, 0);
              tagList.putTagVal(DCM_VerifyingObserverSequence, 1);
              tagList.putTagVal(DCM_InstanceCreationDate, 2);
              tagList.putTagVal(DCM_InstanceCreationTime, 3);
              tagList.putTagVal(DCM_InstanceCreatorUID, 4);
            }
            else if (mode == DVPSY_verifyAndSign_finalize)
            {

              stack.clear();
            }

            if (stack.empty())
              stack.push(&dataset);

            if (pSignatureHandler->createSignature(dataset, stack, tagList, userID, passwd) == EC_Normal)
            {
              DSRDocument *newReport = new DSRDocument();
              if (newReport != NULL)
              {
                if (newReport->read(dataset, DSRTypes::RF_readDigitalSignatures) == EC_Normal)
                {

                  delete pReport;
                  pReport = newReport;
                  pSignatureHandler->updateDigitalSignatureInformation(dataset, DVPSS_structuredReport, OFFalse );
                  if (mode == DVPSY_verifyAndSign_finalize)
                    result = pReport->finalizeDocument();
                  else
                    result = EC_Normal;
                }
              } else
                result = EC_MemoryExhausted;
            }
          }
        }
#else
        DCMPSTAT_LOGFILE("Cannot sign structured report: not compiled with OpenSSL support");
#endif
      } else
        result= EC_Normal;
    }
  }
  return result;
}
