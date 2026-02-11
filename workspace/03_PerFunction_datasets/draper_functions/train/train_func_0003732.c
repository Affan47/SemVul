callAsFunction(ExecState *exec, JSObject *thisObj, const List &args)
{
    KJS_CHECK_THIS( KJS::DOMHashChangeEvent, thisObj );
    DOM::HashChangeEventImpl& hashChangeEvent = *static_cast<DOMHashChangeEvent *>(thisObj)->impl();
    switch (id) {
        case DOMHashChangeEvent::InitHashChangeEvent: {
            hashChangeEvent.initHashChangeEvent(args[0]->toString(exec).domString(),
                                          args[1]->toBoolean(exec),
                                          args[2]->toBoolean(exec),
                                          args[3]->toString(exec).domString(),
                                          args[4]->toString(exec).domString());
            return jsUndefined();
        }
    }
    return jsUndefined();
}
