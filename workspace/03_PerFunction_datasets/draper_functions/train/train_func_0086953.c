fillGetterPropertySlot(PropertySlot& slot, JSValue **location)
{
    GetterSetterImp *gs = static_cast<GetterSetterImp *>(*location);
    JSObject *getterFunc = gs->getGetter();
    if (getterFunc)
        slot.setGetterSlot(this, getterFunc);
    else
        slot.setUndefined(this);
}
