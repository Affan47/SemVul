objundo(mcmcxdef *mctx, objucxdef *undoctx)
{
    ushort prv;
    ushort sav;


    if (undoctx->objucxprv == undoctx->objucxhead)
        errsig(undoctx->objucxerr, ERR_NOUNDO);


    for (prv = undoctx->objucxprv ;; )
    {
        if (undoctx->objucxbuf[prv] == OBJUSAV)
        {
            sav = prv;
            break;
        }


        if (prv == undoctx->objucxtail)
            errsig(undoctx->objucxerr, ERR_ICUNDO);


        memcpy(&prv, &undoctx->objucxbuf[prv+1], sizeof(prv));
    }


    do { obj1undo(mctx, undoctx); } while (undoctx->objucxhead != sav);
}
