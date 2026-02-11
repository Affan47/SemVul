ShowWideCString(const wchar_t * wide_c_str) {
  if (wide_c_str == NULL) return String("(null)");

  return String(internal::WideStringToUtf8(wide_c_str, -1).c_str());
}
