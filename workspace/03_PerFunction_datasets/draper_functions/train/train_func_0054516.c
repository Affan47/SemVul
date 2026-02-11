callAsFunction(ExecState *exec, JSObject *thisObj, const List &args)
{
  KJS_CHECK_THIS( KJS::DOMDocumentFragment, thisObj );
  DOMExceptionTranslator exception(exec);

  DOM::NodeImpl* n = static_cast<DOMDocumentFragment*>(thisObj)->impl();
  DOM::DOMString s = args[0]->toString(exec).domString();

  switch (id) {
  case DOMDocumentFragment::QuerySelector: {
    RefPtr<DOM::ElementImpl> e = n->querySelector(s, exception);
    return getDOMNode(exec, e.get());
  }
  case DOMDocumentFragment::QuerySelectorAll: {
    RefPtr<DOM::NodeListImpl> l = n->querySelectorAll(s, exception);
    return getDOMNodeList(exec, l.get());
  }
  }
  return jsUndefined();
}
