namMethod2Qlinks(const AjPStr method, ajint datatype)
{
    const char* result = NULL;

    result = ajTextaccessMethodGetQlinks(method);

    if(ajCharMatchC(result, "DATA"))
       result = namDatatype2Qlinks(datatype);

    ajDebug("namMethod2Qlinks method: '%S' datatype: %d text: '%s'\n",
           method, datatype, result);

    if(datatype == AJDATATYPE_TEXT)
        return result;

    if(!result)
    {
        if(datatype == AJDATATYPE_ASSEMBLY)
            result = ajAssemaccessMethodGetQlinks(method);
        else if(datatype == AJDATATYPE_FEATURES)
            result = ajFeattabaccessMethodGetQlinks(method);
        else if(datatype == AJDATATYPE_OBO)
            result = ajOboaccessMethodGetQlinks(method);
        else if(datatype == AJDATATYPE_RESOURCE)
            result = ajResourceaccessMethodGetQlinks(method);
        else if(datatype == AJDATATYPE_SEQUENCE)
            result = ajSeqaccessMethodGetQlinks(method);
        else if(datatype == AJDATATYPE_TAXON)
            result = ajTaxaccessMethodGetQlinks(method);
        else if(datatype == AJDATATYPE_URL)
            result = ajUrlaccessMethodGetQlinks(method);
        else if(datatype == AJDATATYPE_VARIATION)
            result = ajVaraccessMethodGetQlinks(method);
        else if(datatype == AJDATATYPE_XML)
            result = ajXmlaccessMethodGetQlinks(method);
    }

    return result;
}
