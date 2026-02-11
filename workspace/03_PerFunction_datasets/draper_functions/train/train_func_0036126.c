callAsFunction(ExecState *exec, JSObject *thisObj, const List &args)
{
  KJS_CHECK_THIS( KJS::DOMMouseEvent, thisObj );
  DOM::MouseEventImpl& mouseEvent = *static_cast<DOMMouseEvent *>(thisObj)->impl();
  switch (id) {
    case DOMMouseEvent::InitMouseEvent:
      mouseEvent.initMouseEvent(args[0]->toString(exec).domString(),
                                args[1]->toBoolean(exec),
                                args[2]->toBoolean(exec),
                                toAbstractView(args[3]),
                                args[4]->toInteger(exec),
                                args[5]->toInteger(exec),
                                args[6]->toInteger(exec),
                                args[7]->toInteger(exec),
                                args[8]->toInteger(exec),
                                args[9]->toBoolean(exec),
                                args[10]->toBoolean(exec),
                                args[11]->toBoolean(exec),
                                args[12]->toBoolean(exec),
                                args[13]->toInteger(exec),
                                toNode(args[14]));
      return jsUndefined();
  }
  return jsUndefined();
}
