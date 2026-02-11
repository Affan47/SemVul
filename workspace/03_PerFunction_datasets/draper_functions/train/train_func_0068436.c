uses(const ContainedPtr& contained) const
{
    {
        ContainedPtr contained2 = ContainedPtr::dynamicCast(_returnType);
        if(contained2 && contained2 == contained)
        {
            return true;
        }
    }

    ExceptionList::const_iterator q;

    for(q = _throws.begin(); q != _throws.end(); ++q)
    {
        ContainedPtr contained2 = ContainedPtr::dynamicCast(*q);
        if(contained2 && contained2 == contained)
        {
            return true;
        }
    }

    return false;
}
