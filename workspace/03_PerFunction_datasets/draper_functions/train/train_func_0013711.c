checkStackChunk( StgPtr sp, StgPtr stack_end )
{
    StgPtr p;

    p = sp;
    while (p < stack_end) {
	p += checkStackFrame( p );
    }

}
