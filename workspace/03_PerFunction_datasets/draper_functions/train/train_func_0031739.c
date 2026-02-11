Multiwrite(String *s) {
    char *find_marker = strstr(Char(s), "(*Stream:");
    while (find_marker) {
      char *next = strstr(find_marker, "*)");
      find_marker += strlen("(*Stream:");

      if (next) {
	int num_chars = next - find_marker;
	String *stream_name = NewString(find_marker);
	Delslice(stream_name, num_chars, Len(stream_name));
	File *fout = Swig_filebyname(stream_name);
	if (fout) {
	  next += strlen("*)");
	  char *following = strstr(next, "(*Stream:");
	  find_marker = following;
	  if (!following)
	    following = next + strlen(next);
	  String *chunk = NewString(next);
	  Delslice(chunk, following - next, Len(chunk));
	  Printv(fout, chunk, NIL);
	}
      }
    }
  }
