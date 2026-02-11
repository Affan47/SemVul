nameGetter(ExecState *exec, JSObject*, const Identifier& propertyName, const PropertySlot& slot)
{
  DOMStyleSheetList *thisObj = static_cast<DOMStyleSheetList *>(slot.slotBase());
  ElementImpl *element = thisObj->m_doc->getElementById(propertyName.domString());
  assert(element->id() == ID_STYLE);
  return getDOMStyleSheet(exec, static_cast<HTMLStyleElementImpl *>(element)->sheet());
}
