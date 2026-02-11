append_rest(struct keymap_sparse **kvp, const int n, const char *text, const int length, const int value)
{
	struct  keymap_sparse	*kp, **pp;
	int	ch = text[n] & (MAPSIZE-1);

	for  (pp = kvp;  (kp = *pp);  pp = &kp->ks_next)
		if  (ch == kp->ks_char)
			goto  found;


	if  ((kp = (struct keymap_sparse *)malloc(sizeof(struct keymap_sparse))) == (struct  keymap_sparse *) 0)
	     nomem();

	kp->ks_char = (char) ch;
	kp->ks_next = (struct  keymap_sparse  *) 0;
	kp->ks_link = (struct  keymap_sparse  *) 0;

	if  (n + 1 >= length)  {
		kp->ks_type = KV_CHAR;
		kp->ks_value = (SHORT) value;
	}
	else  {
		kp->ks_type = KV_SMAP;
		append_rest(&kp->ks_link, n+1, text, length, value);
	}
	*pp = kp;
	return;

found:
	if  (n + 1 >= length)  {
		if  (kp->ks_type & KV_CHAR && kp->ks_value != value)  {
			disp_arg[0] = text[n];
			disp_arg[1] = value;
			disp_arg[2] = kp->ks_value;
			disp_arg[3] = n;
			print_error(9002);
			keyerrors++;
			return;
		}
		kp->ks_type |= KV_CHAR;
		kp->ks_value = (SHORT) value;
	}
	else  {
		kp->ks_type |= KV_SMAP;
		append_rest(&kp->ks_link, n+1, text, length, value);
	}
}
