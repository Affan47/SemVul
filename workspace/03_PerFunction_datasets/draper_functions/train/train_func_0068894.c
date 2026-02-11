applix_read_current_view (ApplixReadState *state, unsigned char *buffer)
{

	unsigned char *ptr;
	while (NULL != (ptr = applix_get_line (state)))
	       if (!a_strncmp (ptr, "End View, Name: ~Current~"))
		       return 0;
	return -1;
}
