icalmemory_resize_buffer(void* buf, size_t size)
{
    void *b = realloc(buf, size);

    if( b == 0){
	icalerror_set_errno(ICAL_NEWFAILED_ERROR);
	return 0;
    }

   return b;
}
