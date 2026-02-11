obj_desc_light(const object_type *o_ptr, char *buf, size_t max, size_t end)
{
	bitflag f[OF_SIZE];

	object_flags(o_ptr, f);


	if ((o_ptr->tval == TV_LIGHT) && !of_has(f, OF_NO_FUEL))
		strnfcat(buf, max, &end, " (%d turns)", o_ptr->timeout);

	return end;
}
