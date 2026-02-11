strip(const_String_or_char_ptr s) {
    Clear(temp);
    Append(temp, s);
    if (Strncmp(s, prefix, Len(prefix)) == 0) {
      Replaceall(temp, prefix, "");
    }
    return Char(temp);
  }
