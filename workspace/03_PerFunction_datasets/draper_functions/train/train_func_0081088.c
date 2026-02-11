DIMSE_dumpMessage(OFString &str, T_DIMSE_C_GetRQ &msg, enum DIMSE_direction dir, DcmItem *dataset, T_ASC_PresentationContextID presID)
{
    OFOStringStream stream;
    const char *uid = dcmFindNameOfUID(msg.AffectedSOPClassUID);

    DIMSE_dumpMessage_start(str, dir);
    stream << "Message Type                  : C-GET RQ" << OFendl;
    if (presID > 0)
    {
        stream << "Presentation Context ID       : " << OFstatic_cast(int, presID) << OFendl;
    }
    stream << "Message ID                    : " << msg.MessageID << OFendl
           << "Affected SOP Class UID        : " << (uid ? uid : msg.AffectedSOPClassUID) << OFendl
           << "Data Set                      : " << ((msg.DataSetType==DIMSE_DATASET_NULL) ? "none" : "present") << OFendl
           << "Priority                      : ";
    switch (msg.Priority)
    {
      case DIMSE_PRIORITY_LOW:
        stream << "low";
        break;
      case DIMSE_PRIORITY_MEDIUM:
        stream << "medium";
        break;
      case DIMSE_PRIORITY_HIGH:
        stream << "high";
        break;
    }

    OFSTRINGSTREAM_GETSTR(stream, result)
    str += result;
    OFSTRINGSTREAM_FREESTR(stream)

    DIMSE_dumpMessage_end(str, dataset);

    return str;
}
