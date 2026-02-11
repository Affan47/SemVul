parse_brackets(IPFilter::Primitive& prim, const Vector<String>& words, int pos,
	       ErrorHandler* errh)
{
  int first_pos = pos + 1;
  String combination;
  for (pos++; pos < words.size() && words[pos] != "]"; pos++)
    combination += words[pos];
  if (pos >= words.size()) {
    errh->error("missing %<]%>");
    return first_pos;
  }
  pos++;


  int fieldpos, len = 1;
  const char* colon = find(combination.begin(), combination.end(), ':');
  const char* comma = find(combination.begin(), combination.end(), ',');
  if (colon < combination.end() - 1) {
    if (cp_integer(combination.begin(), colon, 0, &fieldpos) == colon
	&& cp_integer(colon + 1, combination.end(), 0, &len) == combination.end())
      goto non_syntax_error;
  } else if (comma < combination.end() - 1) {
    int pos2;
    if (cp_integer(combination.begin(), comma, 0, &fieldpos) == comma
	&& cp_integer(comma + 1, combination.end(), 0, &pos2) == combination.end()) {
      len = pos2 - fieldpos + 1;
      goto non_syntax_error;
    }
  } else if (IntArg().parse(combination, fieldpos))
    goto non_syntax_error;
  errh->error("syntax error after %<[%>, expected %<[POS]%> or %<[POS:LEN]%>");
  return pos;

 non_syntax_error:
  int multiplier = 8;
  fieldpos *= multiplier, len *= multiplier;
  if (len < 1 || len > 32)
    errh->error("LEN in %<[POS:LEN]%> out of range, should be between 1 and 4");
  else if ((fieldpos & ~31) != ((fieldpos + len - 1) & ~31))
      errh->error("field [%d:%d] does not fit in a single word", fieldpos/multiplier, len/multiplier);
  else {
    int transp = prim._transp_proto;
    if (transp == IPFilter::UNKNOWN)
      transp = 0;
    prim.set_type(IPFilter::TYPE_FIELD
		  | (transp << IPFilter::FIELD_PROTO_SHIFT)
		  | (fieldpos << IPFilter::FIELD_OFFSET_SHIFT)
		  | ((len - 1) << IPFilter::FIELD_LENGTH_SHIFT), errh);
  }
  return pos;
}
