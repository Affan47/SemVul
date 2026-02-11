processNext()
{
    Rule *rule=prev_processor->getNextRule(); if (rule==NULL) return false;
    RuleElement *re = RuleElement::cast(rule->getFirstByType(re_type));

    if (re == NULL || re->isAny())
    {
        tmp_queue.push_back(rule);
        return true;
    }

    std::list<FWObject*> cl;
    for (FWObject::iterator i=re->begin(); i!=re->end(); i++)
    {
        FWObject *o = FWReference::getObject(*i);
        if (Group::cast(o)!=NULL)  isRecursiveGroup(o->getId(),o);
    }

    tmp_queue.push_back(rule);
    return true;
}
