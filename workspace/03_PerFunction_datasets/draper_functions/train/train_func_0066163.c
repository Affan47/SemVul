toStringPartitionList(const GraphPartitionList& gpl)
{
    StringPartitionList spl;
    for(GraphPartitionList::const_iterator i = gpl.begin(); i != gpl.end(); ++i)
    {
        StringList sl;
        spl.push_back(sl);
        for(ClassList::const_iterator j = i->begin(); j != i->end(); ++j)
        {
            OperationList operations = (*j)->operations();
            for(OperationList::const_iterator l = operations.begin(); l != operations.end(); ++l)
            {
                spl.rbegin()->push_back((*l)->name());
            }
        }
    }
    return spl;
}
