FindAllExtensions(
    const Descriptor* extendee, vector<const FieldDescriptor*>* out) const {
  ExtensionsGroupedByDescriptorMap::const_iterator it =
      extensions_.lower_bound(make_pair(extendee, 0));
  for (; it != extensions_.end() && it->first.first == extendee; ++it) {
    out->push_back(it->second);
  }
}
