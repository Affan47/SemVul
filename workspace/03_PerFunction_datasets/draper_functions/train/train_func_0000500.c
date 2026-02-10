init_context_stack()
{
    static bool did_init = false;
    if ( !did_init ) {
	did_init = true;
	context_stack[0] = current_alloc_context = 0;
    }
}
