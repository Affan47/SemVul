getScriptableExtension(const DOM::HTMLElementImpl &element)
{
  DOM::DocumentImpl* doc = element.document();
  if (doc->part())
    return doc->part()->scriptableExtension(&element);
  return 0L;
}
