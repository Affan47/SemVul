removeAttributeNode( AttrImpl* oldAttr, int& exceptioncode )
{
  if (!oldAttr || oldAttr->ownerElement() != this) {
    exceptioncode = DOMException::NOT_FOUND_ERR;
    return 0;
  }

  if (isReadOnly()) {
    exceptioncode = DOMException::NO_MODIFICATION_ALLOWED_ERR;
    return 0;
  }

  if (!namedAttrMap) {
    exceptioncode = DOMException::NOT_FOUND_ERR;
    return 0;
  }

  return attributes(false)->removeAttr(oldAttr);
}
