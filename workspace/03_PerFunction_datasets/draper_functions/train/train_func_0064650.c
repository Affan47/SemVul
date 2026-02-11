ParseRegExpLiteral(bool seen_equal, bool* ok) {
  if (!scanner().ScanRegExpPattern(seen_equal)) {
    Next();
    ReportMessage("unterminated_regexp", Vector<const char*>::empty());
    *ok = false;
    return NULL;
  }

  int literal_index = temp_scope_->NextMaterializedLiteralIndex();

  Handle<String> js_pattern = NextLiteralString(TENURED);
  scanner().ScanRegExpFlags();
  Handle<String> js_flags = NextLiteralString(TENURED);
  Next();

  return new RegExpLiteral(js_pattern, js_flags, literal_index);
}
