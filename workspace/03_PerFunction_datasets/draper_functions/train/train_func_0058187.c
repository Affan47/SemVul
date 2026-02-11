createRevisedVersion(const OFBool clearList)
{
    OFCondition result = EC_IllegalCall;

    if (getDocumentType() != DT_KeyObjectSelectionDocument)
    {

        if (CompletionFlagEnum == CF_Complete)
        {
            if (clearList)
                PredecessorDocuments.clear();

            result = PredecessorDocuments.addItem(getStringValueFromElement(StudyInstanceUID),
                                                  getStringValueFromElement(SeriesInstanceUID),
                                                  getStringValueFromElement(SOPClassUID),
                                                  getStringValueFromElement(SOPInstanceUID));
            if (result.good())
            {
                IdenticalDocuments.clear();

                CompletionFlagEnum = CF_Partial;
                CompletionFlagDescription.clear();

                ContentDate.clear();
                ContentTime.clear();

                removeVerification();

                DocumentTree.removeSignatures();

                createNewSOPInstance();
            }
        }
    }
    return result;
}
