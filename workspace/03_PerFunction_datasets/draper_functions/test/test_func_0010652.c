FuncPRINT_TO_STREAM (
    Obj                 self,
    Obj                 args )
{
    volatile Obj        arg;
    volatile Obj        stream;
    volatile UInt       i;
    syJmp_buf             readJmpError;


    stream = ELM_LIST(args,1);


    if ( ! OpenOutputStream(stream) ) {
        ErrorQuit( "PrintTo: cannot open stream for output", 0L, 0L );
        return 0;
    }


    for ( i = 2;  i <= LEN_PLIST(args);  i++ ) {
        arg = ELM_LIST(args,i);


        memcpy( readJmpError, ReadJmpError, sizeof(syJmp_buf) );
        if ( ! READ_ERROR() ) {
            if ( IS_PLIST(arg) && 0 < LEN_PLIST(arg) && IsStringConv(arg) ) {
                PrintString1(arg);
            }
            else if ( IS_STRING_REP(arg) ) {
                PrintString1(arg);
            }
            else if ( TNUM_OBJ( arg ) == T_FUNCTION ) {
                PrintObjFull = 1;
                PrintFunction( arg );
                PrintObjFull = 0;
            }
            else {
                PrintObj( arg );
            }
        }
        else {
            CloseOutput();
            memcpy( ReadJmpError, readJmpError, sizeof(syJmp_buf) );
            ReadEvalError();
        }
        memcpy( ReadJmpError, readJmpError, sizeof(syJmp_buf) );
    }


    if ( ! CloseOutput() ) {
        ErrorQuit( "PrintTo: cannot close output", 0L, 0L );
        return 0;
    }

    return 0;
}
