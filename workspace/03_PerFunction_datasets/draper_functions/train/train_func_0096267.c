allot_string(cell capacity, cell fill) {
  data_root<string> str(allot_string_internal(capacity), this);
  fill_string(str.untagged(), 0, capacity, fill);
  return str.untagged();
}
