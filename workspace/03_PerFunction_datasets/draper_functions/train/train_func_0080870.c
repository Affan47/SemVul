destroyChildren()
{
#ifdef DEBUG_DESTROY_CHILDREN
    cerr << "destroyChildren() " << this
         << " name=" << name
         << " type=" << getTypeName()
         << " parent=" << getParent()
         << " path=" << getPath()
         << endl;
#endif

    FWObjectDatabase *dbr = getRoot();
    while (size() > 0)
    {
        FWObject *o = front();

#ifdef DEBUG_DESTROY_CHILDREN
        cerr << "                  " << this
             << " size=" << size()
             << " o=" << o
             << " o->size=" << o->size()
             << endl;
#endif

        if (o)
        {
            if (o->size()) o->destroyChildren();
            if (dbr && !dbr->busy) dbr->removeFromIndex( o->getId() );

#ifdef DEBUG_DESTROY_CHILDREN
            cerr << "                  " << this
                 << " delete " << o
                 << " " << o->name
                 << " " << o->getTypeName()
                 << endl;
#endif

            delete o;
        }
        pop_front();
    }

}
