FuncPrint (
    Obj                 self,
    Obj                 args )
{
    volatile Obj        arg;
    volatile UInt       i;
syJmp_buf           readJmpError;


    for ( i = 1;  i <= LEN_PLIST(args);  i++ ) {
        arg = ELM_LIST(args,i);
        if ( IS_PLIST(arg) && 0 < LEN_PLIST(arg) && IsStringConv(arg) ) {
            PrintString1(arg);
        }
        else if ( IS_STRING_REP(arg) ) {
            PrintString1(arg);
        }
        else if ( TNUM_OBJ( arg ) == T_FUNCTION ) {
	  PrintFunction( arg );
        }
        else {
            memcpy( readJmpError, ReadJmpError, sizeof(syJmp_buf) );


            if ( ! READ_ERROR() ) {
                PrintObj( arg );
            }
            else {
                memcpy( ReadJmpError, readJmpError, sizeof(syJmp_buf) );
                ReadEvalError();
            }
            memcpy( ReadJmpError, readJmpError, sizeof(syJmp_buf) );
        }
    }

    return 0;
}
