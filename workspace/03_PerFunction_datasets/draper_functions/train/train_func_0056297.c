dpush(long data)
{
#ifdef DEBUG_DSTACK
	printf("dpush: sp=%p, data=0x%lx, ", dstack, data);
#endif
	if ( room_on_stack_for(1) )
	{
	    --dstack;
	    *(dstack)=data;
	}
}
