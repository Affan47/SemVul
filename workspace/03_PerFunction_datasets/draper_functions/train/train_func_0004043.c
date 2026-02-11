removeContent(const ContainedPtr& contained)
{
    string scoped = contained->scoped();
    if(!caseSensitive())
    {
        toLower(scoped);
    }
    map<string, ContainedList>::iterator p = _contentMap.find(scoped);
    assert(p != _contentMap.end());
    ContainedList::iterator q;
    for(q = p->second.begin(); q != p->second.end(); ++q)
    {
        if(q->get() == contained.get())
        {
            p->second.erase(q);
            return;
        }
    }
    assert(false);
}
