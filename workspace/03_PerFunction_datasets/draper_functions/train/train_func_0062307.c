Previous()
{
    if (m_ErrorIndex <= 0)
        return;


    int bkp = --m_ErrorIndex;
    while (bkp >= 0)
    {
        if (m_Errors[bkp].lineType == cltError)
        {
            bool isNote =
                ((m_Errors[bkp].errors.GetCount()>0) && m_Errors[bkp].errors[0].StartsWith(_T("note:")));
            if(!isNote)
            {
                m_ErrorIndex = bkp;
                break;
            }
        }
        --bkp;
    }

    DoGotoError(m_Errors[m_ErrorIndex]);
}
