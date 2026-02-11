SerializeWithCachedSizesToArray(
    int start_field_number, int end_field_number,
    uint8* target) const {
  map<int, Extension>::const_iterator iter;
  for (iter = extensions_.lower_bound(start_field_number);
       iter != extensions_.end() && iter->first < end_field_number;
       ++iter) {
    target = iter->second.SerializeFieldWithCachedSizesToArray(iter->first,
                                                               target);
  }
  return target;
}
