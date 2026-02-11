complex2quatern(int count, Pointer from, Pointer to, int itemsize)
{
    int i;


    for (i=count; i>0; i--) {
	memset(to, '\0', itemsize);
	to = DEC(to, itemsize);
	memcpy(from, to, itemsize);
	from = DEC(from, itemsize);
	to = DEC(to, itemsize);
    }

    return OK;
}
