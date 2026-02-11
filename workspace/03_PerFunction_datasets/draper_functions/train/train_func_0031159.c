hasAsyncOps() const
{
    for(ContainedList::const_iterator p = _contents.begin(); p != _contents.end(); ++p)
    {
        ClassDefPtr cl = ClassDefPtr::dynamicCast(*p);
        if(cl && !cl->isLocal())
        {
            OperationList ops = cl->operations();
            if(!ops.empty() && (cl->hasMetaData("ami") || cl->hasMetaData("amd")))
            {
                return true;
            }
            for(OperationList::const_iterator i = ops.begin(); i != ops.end(); ++i)
            {
                OperationPtr op = *i;
                if(op->hasMetaData("ami") || op->hasMetaData("amd"))
                {
                    return true;
                }
            }
        }

        ContainerPtr container = ContainerPtr::dynamicCast(*p);
        if(container && container->hasAsyncOps())
        {
            return true;
        }
    }

    return false;
}
