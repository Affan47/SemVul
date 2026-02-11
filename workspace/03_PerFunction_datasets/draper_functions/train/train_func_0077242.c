FuncREAD_STRING_FILE (
    Obj             self,
    Obj             fid )
{
    Char            buf[20001];
    Int             ret, len;
    UInt            lstr;
    Obj             str;


    while ( ! IS_INTOBJ(fid) ) {
        fid = ErrorReturnObj(
            "<fid> must be an integer (not a %s)",
            (Int)TNAM_OBJ(fid), 0L,
            "you can replace <fid> via 'return <fid>;'" );
    }

#if ! SYS_IS_CYGWIN32

#if HAVE_STAT


    {
        struct stat fstatbuf;
        if ( syBuf[INT_INTOBJ(fid)].pipe == 0 &&
             fstat( syBuf[INT_INTOBJ(fid)].fp,  &fstatbuf) == 0 ) {
            len = fstatbuf.st_size;
            str = NEW_STRING( len );
            ret = read( syBuf[INT_INTOBJ(fid)].fp,
                        CHARS_STRING(str), len);
            CHARS_STRING(str)[ret] = '\0';
            SET_LEN_STRING(str, ret);
            if ( ret == len ) {
                 return str;
            }
        }
    }
#endif
#endif

    str = NEW_STRING(0);
    len = 0;
    while (1) {
        if ( (ret = read( syBuf[INT_INTOBJ(fid)].fp , buf, 20000)) <= 0 )
            break;
        len += ret;
        GROW_STRING( str, len );
	lstr = GET_LEN_STRING(str);
        memcpy( CHARS_STRING(str)+lstr, buf, ret );
	*(CHARS_STRING(str)+lstr+ret) = '\0';
	SET_LEN_STRING(str, lstr+ret);
    }


    len = GET_LEN_STRING(str);
    ResizeBag( str, SIZEBAG_STRINGLEN(len) );


    syBuf[INT_INTOBJ(fid)].ateof = 1;
    return len == 0 ? Fail : str;
}
