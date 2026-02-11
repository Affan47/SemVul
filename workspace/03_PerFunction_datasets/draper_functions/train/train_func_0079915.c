lbnRealloc(void *oldptr, unsigned oldbytes, unsigned newbytes)
{
	void *newptr = lbnMemAlloc(newbytes);

	if (!newptr)
		return newptr;
	if (!oldptr)
		return BIGLITTLE((char *)newptr+newbytes, newptr);


	if (newbytes > oldbytes) {
		BIG(newptr = (char *)newptr + newbytes;)
		BIG(oldptr = (char *)oldptr - oldbytes;)
		memcpy(BIGLITTLE((char *)newptr-oldbytes, newptr), oldptr,
		       oldbytes);
	} else {
		memcpy(newptr, BIGLITTLE((char *)oldptr-newbytes, oldptr),
		       newbytes);
		BIG(newptr = (char *)newptr + newbytes;)
		BIG(oldptr = (char *)oldptr - oldbytes;)
	}

	lbnMemFree(oldptr, oldbytes);

	return newptr;
}
