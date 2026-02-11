dispatch(Host *obj1, void *_obj2)
{
    FWObject *obj2 = (FWObject*)(_obj2);


    bool res = true;
    list<FWObject*> all_interfaces;
    Interface::findAllInterfaces(obj1, all_interfaces);
    for (list<FWObject*>::iterator it = all_interfaces.begin();
         it != all_interfaces.end(); ++it)
    {
        res &= checkComplexMatchForSingleAddress(Interface::cast(*it), obj2);
    }
    return res ? obj1 : NULL;
}
