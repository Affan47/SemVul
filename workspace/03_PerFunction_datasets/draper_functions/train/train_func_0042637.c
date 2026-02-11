href() const
{
    if(!impl) return DOMString();
    DOMString href = static_cast<ElementImpl*>(impl)->getAttribute(ATTR_HREF);
    return !href.isNull() ? impl->document()->completeURL(href.string()) : href;
}
