checkIntroduced(const string& scoped, ContainedPtr namedThing)
{
    if(scoped[0] == ':')
    {
        return true;
    }


    string::size_type pos = scoped.find("::");
    string firstComponent = pos == string::npos ? scoped : scoped.substr(0, pos);


    if(namedThing == 0)
    {
        ContainedList cl = lookupContained(firstComponent, false);
        if(namedThing == 0)
        {
            if(cl.empty())
            {
                return true;
            }
        }
        namedThing = cl.front();
    }
    else
    {


        ContainerPtr c;
        bool first = true;
        while(pos != string::npos)
        {
            if(first)
            {
                c = namedThing->container();
            }
            else
            {
                ContainedPtr contained = ContainedPtr::dynamicCast(c);
                if(contained)
                {
                    c = contained->container();
                }
            }
            first = false;
            if(pos != string::npos)
            {
                pos = scoped.find("::", pos + 2);
            }
        }
        if(ContainedPtr::dynamicCast(c))
        {
            namedThing = ContainedPtr::dynamicCast(c);
        }
    }


    map<string, ContainedPtr, CICompare>::const_iterator it = _introducedMap.find(firstComponent);
    if(it == _introducedMap.end())
    {


        _introducedMap[firstComponent] = namedThing;
    }
    else
    {


        if(!_unit->caseSensitive() && it->second != namedThing)
        {
            _unit->error("`" + firstComponent + "' has changed meaning");
            return false;
        }
    }
    return true;
}
