findStylesheetByUuid(const std::string &uuid) const
{
    PD_RDFSemanticStylesheetHandle ret;
    if( uuid.empty() )
        return ret;

    PD_RDFSemanticStylesheets ssl = stylesheets();
    for( PD_RDFSemanticStylesheets::iterator iter = ssl.begin(); iter != ssl.end(); ++iter )
    {
        PD_RDFSemanticStylesheetHandle ss = *iter;
        if ( ss->uuid() == uuid )
        {
            return ss;
        }
    }
    return ret;
}
