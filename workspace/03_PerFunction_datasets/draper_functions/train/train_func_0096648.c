uap_stack_pointer(void *uap)
{


	if(in_code_heap_p(UAP_PROGRAM_COUNTER(uap)))
	{
		F_STACK_FRAME *ptr = ucontext_stack_pointer(uap);
		if(!ptr)
			critical_error("Invalid uap",(CELL)uap);
		return ptr;
	}
	else
		return NULL;
}
