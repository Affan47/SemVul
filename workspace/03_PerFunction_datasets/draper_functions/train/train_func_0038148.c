do_test_call(gboolean result, const char* test_title, const char* filename,
             int line )
{
    if (result)
        success_args( test_title, filename, line, "" );
    else
        failure_args( test_title, filename, line, "" );

    return result;
}
