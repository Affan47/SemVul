trace_SQLAllocEnv(int trace_leave, int retcode,
    SQLHENV	* phenv)
{

  _trace_print_function (en_AllocEnv, trace_leave, retcode);


  _trace_handle_p (SQL_HANDLE_ENV, phenv, TRACE_OUTPUT_SUCCESS);
}
