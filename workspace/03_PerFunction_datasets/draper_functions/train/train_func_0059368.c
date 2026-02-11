auto_name(const char*prefix, char pad, const char* suffix)
{
      char tmp[32];
      int pad_pos = strlen(prefix);
      int max_pos = sizeof(tmp) - strlen(suffix) - 1;
      strncpy(tmp, prefix, sizeof(tmp));
      while (pad_pos <= max_pos) {
	    strcat(tmp + pad_pos, suffix);
	    hname_t new_name(lex_strings.make(tmp));
	    if (!up_->child(new_name)) {
		  name_ = new_name;
		  return true;
	    }
	    tmp[pad_pos++] = pad;
      }
      return false;
}
