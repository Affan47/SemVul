JS_XDRValue(JSXDRState *xdr, jsval *vp)
{
    uint32 type;

    if (xdr->mode == JSXDR_ENCODE) {
        if (JSVAL_IS_NULL(*vp))
            type = JSVAL_XDRNULL;
        else if (JSVAL_IS_VOID(*vp))
            type = JSVAL_XDRVOID;
        else
            type = JSVAL_TAG(*vp);
    }
    return JS_XDRUint32(xdr, &type) && XDRValueBody(xdr, type, vp);
}
