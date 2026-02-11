enterAllocContext()
{
    static int context_seq_no = 0;
    init_context_stack();
    if ( context_ptr+1 == MAX_CONTEXTS ) {
#if defined(QT_CHECK_STATE)
	qWarning( "QColor::enterAllocContext: Context stack overflow" );
#endif
	return 0;
    }
    current_alloc_context = context_stack[++context_ptr] = ++context_seq_no;
    return current_alloc_context;
}
