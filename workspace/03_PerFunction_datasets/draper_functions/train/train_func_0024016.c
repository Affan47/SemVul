processNext()
{
    Rule *rule = prev_processor->getNextRule();
    if (rule==NULL) return false;

    if (compiler->group_registry != NULL)
    {
        RuleElement *re = RuleElement::cast(rule->getFirstByType(re_type));

        for (FWObject::iterator i=re->begin(); i!=re->end(); i++)
        {
            FWObject *obj = FWReference::getObject(*i);
            if (ObjectGroup::cast(obj)!=NULL && obj->size() > 0)
            {
                compiler->registerGroupObject(re, ObjectGroup::cast(obj));
            }
        }
    }

    tmp_queue.push_back(rule);
    return true;
}
