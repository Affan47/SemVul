visitClassDefEnd(const ClassDefPtr& p)
{
    string scoped = fixKwd(p->scoped());
    string scope = fixKwd(p->scope());

    H << nl << nl << _dllExport << "static const ::std::string& ice_staticId();";
    H << eb << ';';

    string flatName = p->flattenedScope() + p->name() + "_ids";

    StringList ids;
    getIds(p, ids);

    StringList::const_iterator firstIter = ids.begin();
    StringList::const_iterator scopedIter = find(ids.begin(), ids.end(), p->scoped());
    assert(scopedIter != ids.end());
    StringList::difference_type scopedPos = ice_distance(firstIter, scopedIter);

    C << sp;
    C << nl << "const ::std::string&" << nl << "IceProxy" << scoped << "::ice_staticId()";
    C << sb;
    C << nl << "return " << flatName << '[' << scopedPos << "];";
    C << eb;

    _useWstring = resetUseWstring(_useWstringHist);
}
