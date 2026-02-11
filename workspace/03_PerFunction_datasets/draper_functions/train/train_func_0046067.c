READ_COMMAND ( void ) {

    ExecStatus    status;

    ClearError();
    status = ReadEvalCommand(BottomLVars);
    if( status == STATUS_EOF )
        return 0;

    if ( UserHasQuit || UserHasQUIT )
        return 0;


    if ( status & (STATUS_RETURN_VAL | STATUS_RETURN_VOID) ) {
        Pr( "'return' must not be used in file read-eval loop", 0L, 0L );
    }


    else if (status == STATUS_QUIT) {
        RecursionDepth = 0;
        UserHasQuit = 1;
    }
    else if (status == STATUS_QQUIT) {
        UserHasQUIT = 1;
    }
    ClearError();

    return 1;
}
