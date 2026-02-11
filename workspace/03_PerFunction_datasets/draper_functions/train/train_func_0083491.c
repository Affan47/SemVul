type_engine_import_sfun( Chuck_Env * env, Chuck_DL_Func * sfun )
{
    a_Func_Def func_def = NULL;


    if( !env->class_def )
    {

        EM_error2( 0,
            "import error: import_sfun '%s' invoked between begin/end",
            sfun->name.c_str() );
        return FALSE;
    }


    func_def = make_dll_as_fun( sfun, TRUE );


    if( !type_engine_scan1_func_def( env, func_def ) )
        return FALSE;
    if( !type_engine_scan2_func_def( env, func_def ) )
        return FALSE;
    if( !type_engine_check_func_def( env, func_def ) )
        return FALSE;

    return TRUE;
}
