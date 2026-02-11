function_location( FUNCTION * function_, OBJECT * * file, int * line )
{
    if ( function_->type == FUNCTION_BUILTIN )
    {
        *file = constant_builtin;
        *line = -1;
    }
#ifdef HAVE_PYTHON
    if ( function_->type == FUNCTION_PYTHON )
    {
        *file = constant_builtin;
        *line = -1;
    }
#endif
    else
    {
        JAM_FUNCTION * function = (JAM_FUNCTION *)function_;
        assert( function_->type == FUNCTION_JAM );
        *file = function->file;
        *line = function->line;
    }
}
