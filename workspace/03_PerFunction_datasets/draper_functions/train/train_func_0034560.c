READ_AS_FUNC ( void )
{
    Obj                 func;
    UInt                type;


    ClearError();
    type = ReadEvalFile();


    if ( type == 0 ) {
        func = ReadEvalResult;
    }
    else {
        func = Fail;
    }


    if ( ! CloseInput() ) {
        ErrorQuit(
            "Panic: READ_AS_FUNC cannot close input, this should not happen",
            0L, 0L );
    }
    ClearError();


    return func;
}
