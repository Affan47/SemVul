visitStructStart(const StructPtr& p)
{
    _useWstring = setUseWstring(p, _useWstringHist, _useWstring);

    string name = fixKwd(p->name());

    H << sp << nl << "struct " << name;
    H << sb;

    return true;
}
