function_unbind_variables( FUNCTION * f )
{
    if ( f->type == FUNCTION_JAM )
    {
        JAM_FUNCTION * const func = (JAM_FUNCTION *)f;
        return func->generic ? func->generic : f;
    }
#ifdef HAVE_PYTHON
    if ( f->type == FUNCTION_PYTHON )
        return f;
#endif
    assert( f->type == FUNCTION_BUILTIN );
    return f;
}
