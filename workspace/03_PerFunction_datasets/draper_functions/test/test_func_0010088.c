ei_x_encode_empty_list(ei_x_buff* x)
{
    int i = x->index;
    if (ei_encode_empty_list(NULL, &i) == -1)
      return -1;
    if (!x_fix_buff(x, i))
	return -1;
    return ei_encode_empty_list(x->buff, &x->index);
}
