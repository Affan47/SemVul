callAsFunction(ExecState *exec, JSObject *thisObj, const List &args)
{
  KJS_CHECK_THIS( KJS::DOMNamedNodeMap, thisObj );
  DOMExceptionTranslator exception(exec);
  DOM::NamedNodeMapImpl& map = *static_cast<DOMNamedNodeMap *>(thisObj)->impl();

  switch(id) {
    case DOMNamedNodeMap::GetNamedItem:
      return getDOMNode(exec, map.getNamedItem(args[0]->toString(exec).domString()));
    case DOMNamedNodeMap::SetNamedItem: {
      DOM::Node old = map.setNamedItem(toNode(args[0]),exception);
      return getDOMNode(exec, old.handle());
    }
    case DOMNamedNodeMap::RemoveNamedItem: {
      DOM::Attr toRet = map.removeNamedItem(args[0]->toString(exec).domString(), exception);
      return getDOMNode(exec, toRet.handle());
    }
    case DOMNamedNodeMap::Item:
      return getDOMNode(exec, map.item(args[0]->toInt32(exec)));
    case DOMNamedNodeMap::GetNamedItemNS: {
      DOM::Node old = map.getNamedItemNS(args[0]->toString(exec).domString(),args[1]->toString(exec).domString());
      return getDOMNode(exec, old.handle());
    }
    case DOMNamedNodeMap::SetNamedItemNS: {
      DOM::Node old = map.setNamedItemNS(toNode(args[0]),exception);
      return getDOMNode(exec, old.handle());
    }
    case DOMNamedNodeMap::RemoveNamedItemNS: {
      DOM::Node old = map.removeNamedItemNS(args[0]->toString(exec).domString(),args[1]->toString(exec).domString(),exception);
      return getDOMNode(exec, old.handle());
    }
    default:
      break;
  }

  return jsUndefined();
}
