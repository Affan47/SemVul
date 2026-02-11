allDataMembers() const
{
    DataMemberList result;


    if(!_bases.empty() && !_bases.front()->isInterface())
    {
        result = _bases.front()->allDataMembers();
    }


    DataMemberList myMembers = dataMembers();
    result.splice(result.end(), myMembers);

    return result;
}
