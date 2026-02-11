FuncWRITE_STRING_FILE_NC (
    Obj             self,
    Obj             fid,
    Obj             str )
{
    Int             len = 0, ret;


    len = GET_LEN_STRING(str);
    ret = write( syBuf[INT_INTOBJ(fid)].echo, CHARS_STRING(str), len);
    return (ret == len)?True : Fail;
}
