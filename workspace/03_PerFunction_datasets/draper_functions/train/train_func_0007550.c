collectClassMembers(const ClassDefPtr& p, MemberInfoList& allMembers, bool inherited)
{
    ClassList bases = p->bases();
    if(!bases.empty() && !bases.front()->isInterface())
    {
        collectClassMembers(bases.front(), allMembers, true);
    }

    DataMemberList members = p->dataMembers();

    for(DataMemberList::iterator q = members.begin(); q != members.end(); ++q)
    {
        MemberInfo m;
        m.fixedName = fixIdent((*q)->name());
        m.type = (*q)->type();
        m.inherited = inherited;
        m.metaData = (*q)->getMetaData();
        allMembers.push_back(m);
    }
}
