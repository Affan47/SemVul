ei_x_encode_string_len(ei_x_buff* x, const char* s, int len)
{
    int i = x->index;
    if (ei_encode_string_len(NULL, &i, s, len) == -1)
      return -1;
    if (!x_fix_buff(x, i))
	return -1;
    return ei_encode_string_len(x->buff, &x->index, s, len);
}
