stuff_vec3d_list(vec3d *vlp, int max_vecs)
{
	int	count = 0;

	ignore_white_space();

	if (*Mp != '(') {
		error_display(1, "Reading vec3d list.  Found [%c].  Expecting '('.\n", *Mp);
		longjmp(parse_abort, 6);
	}

	Mp++;

	ignore_white_space();

	while (*Mp != ')') {
		Assert(count < max_vecs);
		if (count < max_vecs) {
			stuff_parenthesized_vec3d(&vlp[count++]);
		} else {
			vec3d temp;
			stuff_parenthesized_vec3d(&temp);
		}

		ignore_white_space();
	}

	Mp++;

	return count;
}
