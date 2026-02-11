hard_map_offset(int offset, const int *begin, const int *end)
{
    while (begin != end) {
	const int *mid = begin + (((end - begin) >> 2) << 1);
	if (mid[0] == offset)
	    return mid[1];
	else if (mid[0] < offset)
	    begin = mid + 2;
	else
	    end = begin;
    }
    return offset;
}
