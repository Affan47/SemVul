hasDataOnlyClasses() const
{
    for(ContainedList::const_iterator p = _contents.begin(); p != _contents.end(); ++p)
    {
        ClassDefPtr q = ClassDefPtr::dynamicCast(*p);
        if(q)
        {
            if(!q->isAbstract())
            {
                return true;
            }
        }

        ContainerPtr container = ContainerPtr::dynamicCast(*p);
        if(container && container->hasDataOnlyClasses())
        {
            return true;
        }
    }

    return false;
}
