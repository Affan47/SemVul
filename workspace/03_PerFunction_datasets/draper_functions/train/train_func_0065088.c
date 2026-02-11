uses(const ContainedPtr& contained) const
{
    ContainedPtr contained2 = ContainedPtr::dynamicCast(_type);
    if(contained2 && contained2 == contained)
    {
        return true;
    }

    return false;
}
