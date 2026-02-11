fixTree()
{
    getRoot()->addToIndex(this);
    for(list<FWObject*>::iterator m=begin(); m!=end(); ++m)
    {
        FWObject *o = *m;
        if (o->getRoot() != getRoot()) o->setRoot(getRoot());
        if (o->getParent() != this) o->setParent(this);
        getRoot()->addToIndex(o);
        o->fixTree();
    }
}
