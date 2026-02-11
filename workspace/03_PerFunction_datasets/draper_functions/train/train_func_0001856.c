FuncLOAD_STAT (
    Obj                 self,
    Obj                 filename,
    Obj                 crc )
{
    StructInitInfo *    info = 0;
    Obj                 crc1;
    Int                 k;
    Int                 res;


    while ( ! IsStringConv( filename ) ) {
        filename = ErrorReturnObj(
            "<filename> must be a string (not a %s)",
            (Int)TNAM_OBJ(filename), 0L,
            "you can replace <filename> via 'return <filename>;'" );
    }
    while ( !IS_INTOBJ(crc) && crc!=False ) {
        crc = ErrorReturnObj(
            "<crc> must be a small integer or 'false' (not a %s)",
            (Int)TNAM_OBJ(crc), 0L,
            "you can replace <crc> via 'return <crc>;'" );
    }


    for ( k = 0;  CompInitFuncs[k];  k++ ) {
        info = (*(CompInitFuncs[k]))();
        if ( info == 0 ) {
            continue;
        }
        if ( ! strcmp( CSTR_STRING(filename), info->name ) ) {
            break;
        }
    }
    if ( CompInitFuncs[k] == 0 ) {
        if ( SyDebugLoading ) {
            Pr( "#I  LOAD_STAT: no module named '%s' found\n",
                (Int)CSTR_STRING(filename), 0L );
        }
        return False;
    }


    if ( crc != False ) {
        crc1 = INTOBJ_INT( info->crc );
        if ( ! EQ( crc, crc1 ) ) {
            if ( SyDebugLoading ) {
                Pr( "#I  LOAD_STAT: crc values do not match, gap ", 0L, 0L );
                PrintInt( crc );
                Pr( ", stat ", 0L, 0L );
                PrintInt( crc1 );
                Pr( "\n", 0L, 0L );
            }
            return False;
        }
    }


    info->isGapRootRelative = 0;
    res = (info->initKernel)(info);
    UpdateCopyFopyInfo();


    ExecBegin( BottomLVars );
    res = res || (info->initLibrary)(info);
    ExecEnd(res ? STATUS_ERROR : STATUS_END);
    if ( res ) {
        Pr( "#W  init functions returned non-zero exit code\n", 0L, 0L );
    }
    RecordLoadedModule(info, CSTR_STRING(filename));

    return True;
}
