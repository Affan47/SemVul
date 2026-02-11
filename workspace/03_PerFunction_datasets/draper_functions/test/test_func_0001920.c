PrintChangesTo(StringStream* stream) {
  int changes_flags = ChangesFlags();
  if (changes_flags == 0) return;
  stream->Add(" changes[");
  if (changes_flags == AllSideEffects()) {
    stream->Add("*");
  } else {
    bool add_comma = false;
#define PRINT_DO(type)                         \
    if (changes_flags & (1 << kChanges##type)) { \
      if (add_comma) stream->Add(",");           \
      add_comma = true;                          \
      stream->Add(#type);                        \
    }
    GVN_FLAG_LIST(PRINT_DO);
#undef PRINT_DO
  }
  stream->Add("]");
}
