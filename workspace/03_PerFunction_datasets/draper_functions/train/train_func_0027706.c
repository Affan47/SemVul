operator=(const interval &rhs)
{
    if (this != &rhs)
    {
	if (rhs.empty())
	    clear();
	else
	{
	    if (rhs.length > size)
	    {
		for (;;)
		{
		    size = size * 2 + 8;
		    if (rhs.length <= size)
			break;
		}
		delete [] data;
		data = new data_t [size + 1];
	    }
	    length = rhs.length;
	    for (size_t j = 0; j < length; ++j)
		data[j] = rhs.data[j];
	    data[length] = length;
	}
    }
    return *this;
}
