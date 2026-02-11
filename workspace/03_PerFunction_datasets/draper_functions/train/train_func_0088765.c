writeEndCode(Output& out, const ParamDeclList& params, const TypePtr& ret, const StringList& metaData)
{
    for(ParamDeclList::const_iterator p = params.begin(); p != params.end(); ++p)
    {
        writeParamEndCode(out, (*p)->type(), fixKwd((*p)->name()), (*p)->getMetaData());
    }
    if(ret)
    {
	writeParamEndCode(out, ret, "__ret", metaData);
    }
}
