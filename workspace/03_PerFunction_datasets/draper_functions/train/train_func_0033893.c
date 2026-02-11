OGRGFTExtractTableID(const char* pszTableID,
                                      CPLString& osReminder)
{
    CPLString osTableId(pszTableID);
    if (osTableId.size() > 1 &&
        (osTableId[0] == '"' || osTableId[0] == '\''))
    {
        char chFirstChar = osTableId[0];
        osTableId.erase(0, 1);
        for(int i=0;i<(int)osTableId.size();i++)
        {
            if (osTableId[i] == chFirstChar)
            {
                osReminder = osTableId.substr(i+1);
                osTableId.resize(i);
                break;
            }
        }
    }
    else
    {
        for(int i=0;i<(int)osTableId.size();i++)
        {
            if (osTableId[i] == ' ')
            {
                osReminder = osTableId.substr(i);
                osTableId.resize(i);
                break;
            }
        }
    }
    return osTableId;
}
