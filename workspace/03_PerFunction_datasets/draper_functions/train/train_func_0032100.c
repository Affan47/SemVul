LOC_pad_create(const char *pad)
{
    if (*pad == 0)
	return OK;
    else if (find_pad(pad) != NULL)
	return DUPLICATE;
    else if (create_pad(pad))
	return OK;
    else
	return NO_MEMORY;
}
