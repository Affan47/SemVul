toEvent(JSValue *val)
{
  JSObject *obj = val->getObject();
  if (!obj || !obj->inherits(&DOMEvent::info))
    return 0;

  const DOMEvent *dobj = static_cast<const DOMEvent*>(obj);
  return dobj->impl();
}
