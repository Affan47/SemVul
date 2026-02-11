compile_while(
	PARSE	*p,
	LOL	*args,
	int	*jmp )
{
	LIST *result = 0;
	LIST *l;


	while( ( *jmp == JMP_NONE ) &&
	       ( l = (*p->left->func)( p->left, args, jmp ) ) )
	{


	    list_free( l );


	    list_free( result );
	    result = (*p->right->func)( p->right, args, jmp );


	    if( *jmp == JMP_CONTINUE )
		*jmp = JMP_NONE;
	}


	if( *jmp == JMP_BREAK || *jmp == JMP_CONTINUE )
	    *jmp = JMP_NONE;


	return result;
}
