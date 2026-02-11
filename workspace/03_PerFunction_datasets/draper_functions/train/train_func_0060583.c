addRef(FWObject *obj)
{
    FWObject *o=NULL;
    if (isAny())
    {
	o=(*(begin()));
	o=(FWReference::cast(o))->getPointer();
    }
    FWObject::addRef(obj);
    if (o!=NULL) removeRef(o);
}
