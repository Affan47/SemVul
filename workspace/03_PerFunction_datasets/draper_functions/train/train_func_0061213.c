AssRecHandler (
    Obj                 self,
    Obj                 rec,
    Obj                 rnam,
    Obj                 obj )
{
    ASS_REC( rec, INT_INTOBJ(rnam), obj );
    return 0;
}
