record_obj(unsigned long handle, unsigned long obj)
{


	WRITE_ONCE(*(unsigned long *)handle, obj);
}
