addToIndexRecursive(FWObject *o)
{
    addToIndex(o);
    for (FWObject::iterator i=o->begin(); i!=o->end(); ++i)
        addToIndexRecursive(*i);
}
