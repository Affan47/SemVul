m6805_set_context(void *src)
{
	if( src )
	{
		m6805 = *(m6805_Regs*)src;
		S = SP_ADJUST( S );
	}
}
