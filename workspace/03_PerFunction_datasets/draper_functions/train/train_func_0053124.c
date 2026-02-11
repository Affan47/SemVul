getName(size_t len) const
{
    H5std_string attr_name;
    ssize_t name_size = getName(attr_name, len);
    if (name_size < 0)
	return("");
    else
	return(attr_name);
}
