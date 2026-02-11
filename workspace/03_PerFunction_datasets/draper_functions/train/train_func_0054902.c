putVal(const tstring& name, void* object)
{
    ObjectMap::value_type value(name, object);
    OFPair<ObjectMap::iterator, bool> ret;

    {
        thread::MutexGuard guard (mutex);
        ret = data.insert(value);
    }

    if (! ret.second)
        deleteObject( value.second );
    return ret.second;
}
