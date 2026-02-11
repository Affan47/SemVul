cmp(const FWObject *obj, bool recursive) throw(FWException)
{
    if (getTypeName() != obj->getTypeName() || name != obj->name || comment != obj->comment || ro != obj->ro)
        return false;

    if (data.size() != obj->data.size())
        return false;

    for(map<string, string>::const_iterator i=data.begin(); i!=data.end(); ++i)
    {
        const string &name  = (*i).first;
        const string &value = (*i).second;

        map<string,string>::const_iterator j=obj->data.find(name);
        if (j==obj->data.end()) return false;
        if (j->second!=value) return false;
    }

    if (keywords.empty() != obj->keywords.empty() || keywords != obj->keywords)
        return false;

    if (recursive)
    {
        if (size()!=obj->size())  return false;


        std::set<FWObject*> matched;
        FWObject::const_iterator i1=begin();
        for ( ; i1!=end(); ++i1)
        {
            bool found_equal_child_object=false;
            FWObject::const_iterator j1=obj->begin();
            for ( ; j1!=obj->end(); ++j1)
            {
                if ((*i1)->cmp(*j1, recursive))
                {
                    if (matched.find(*j1) == matched.end())
                    {
                        matched.insert(*j1);
                        found_equal_child_object = true;
                        break;
                    }

                }
            }
            if (!found_equal_child_object) return false;
        }
    }
    return true;
}
