getOwnPropertySlot(ExecState *exec, const Identifier &propertyName, PropertySlot& slot)
{
#ifdef KJS_VERBOSE
  kDebug(6070) << "KJS::HTMLDocument::getOwnPropertySlot " << propertyName.qstring();
#endif

  DOM::DocumentImpl* docImpl = impl();
  KHTMLPart *part = docImpl->part();

  Window* win = part ? Window::retrieveWindow(part) : 0L;
  if ( !win || !win->isSafeScript(exec) ) {
    slot.setUndefined(this);
    return true;
  }

  DOM::DOMString  propertyDOMString = propertyName.domString();


  ElementMappingCache::ItemInfo* info = docImpl->underDocNamedCache().get(propertyDOMString);
  if (info) {


    bool matched = false;
    if (info->nd && DOM::HTMLMappedNameCollectionImpl::matchesName(info->nd,
                              HTMLCollectionImpl::DOCUMENT_NAMED_ITEMS, propertyDOMString)) {
        matched = true;
    } else {

        DOM::HTMLMappedNameCollectionImpl coll(impl(), HTMLCollectionImpl::DOCUMENT_NAMED_ITEMS, propertyDOMString);
        matched = coll.firstItem() != 0;
    }

    if (matched) {
        slot.setCustom(this, nameGetter);
        return true;
    }
  }


  if ( part ) {
    if (part->findFrame( propertyName.qstring() )) {
      slot.setCustom(this, frameNameGetter);
      return true;
    }
  }


  const HashEntry* entry = Lookup::findEntry(&HTMLDocumentTable, propertyName);
  if (entry && !isLateProperty(entry->value)) {
    getSlotFromEntry<HTMLDocFunction, HTMLDocument>(entry, this, slot);
    return true;
  }


  JSValue **val = getDirectLocation(propertyName);
  if (val) {
    fillDirectLocationSlot(slot, val);
    return true;
  }


  if (entry) {
    getSlotFromEntry<HTMLDocFunction, HTMLDocument>(entry, this, slot);
    return true;
  }

  return DOMDocument::getOwnPropertySlot(exec, propertyName, slot);
}
