_findDependencies_internal(FWObject *obj,
                                          list<FWObject*> &deps,
                                          int anti_loop_id)
{
    if (obj==NULL) return;
    if (FWOptions::cast(obj)) return;
    if (FWReference::cast(obj)!=NULL)
    {
        _findDependencies_internal(FWReference::cast(obj)->getPointer(),
                                   deps, anti_loop_id);
    } else
    {
        if (obj->getInt(".anti_loop")==anti_loop_id) return;
        obj->setInt(".anti_loop", anti_loop_id);

        if (!RuleElement::cast(obj) && !Rule::cast(obj) && !RuleSet::cast(obj))
            deps.push_back(obj);

        if (Group::cast(obj) || RuleSet::cast(obj) || Host::cast(obj))
        {
            for (FWObject::iterator j1=obj->begin(); j1!=obj->end(); ++j1)
            {
                FWObject *o = *j1;
                _findDependencies_internal(o, deps, anti_loop_id);
            }
        }
    }
}
