setGroupRegistryKey(FWObject *obj, const std::string &key)
{
    obj->setStr(".group_registry_key", key);
    for (FWObject::iterator i=obj->begin(); i!=obj->end(); i++)
    {
        setGroupRegistryKey(*i, key);
    }
}
