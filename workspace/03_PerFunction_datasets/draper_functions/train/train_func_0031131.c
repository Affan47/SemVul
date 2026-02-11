classDataMembers() const
{
    DataMemberList result;
    for(ContainedList::const_iterator p = _contents.begin(); p != _contents.end(); ++p)
    {
        DataMemberPtr q = DataMemberPtr::dynamicCast(*p);
        if(q)
        {
            BuiltinPtr builtin = BuiltinPtr::dynamicCast(q->type());
            if((builtin && builtin->kind() == Builtin::KindObject) || ClassDeclPtr::dynamicCast(q->type()))
            {
                result.push_back(q);
            }
        }
    }
    return result;
}
