clear() {
  ALIterator it;
  for( First(it); !Done(it); ) {
    Attribute* attr = GetAttr(it);
    Remove(it);
    Resource::unref(attr);
  }
}
