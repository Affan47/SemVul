FuncFUNC_BODY_SIZE(Obj self, Obj f)
{
    Obj body;
    if (TNUM_OBJ(f) != T_FUNCTION) return Fail;
    body = BODY_FUNC(f);
    if (body == 0) return INTOBJ_INT(0);
    else return INTOBJ_INT( SIZE_BAG( body ) );
}
