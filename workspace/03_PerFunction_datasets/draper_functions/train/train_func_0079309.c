emit_then( void )
{
    emit_token("b(>resolve)");
    if ( control_stack != NULL )
    {
	if ( control_stack->cs_tag == WHILE_CSTAG )
	{
	    control_stack->cs_tag = IF_CSTAG;
	}
    }
    resolve_forward( IF_CSTAG );
}
