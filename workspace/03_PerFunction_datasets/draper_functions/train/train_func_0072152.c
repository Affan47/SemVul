file_type(FDSC ** curr, char *fixed)
{
    FDSC **this;

    if ((this = file_find(curr, fixed)))
	return (*this)->type;
    return fdt_none;
}
