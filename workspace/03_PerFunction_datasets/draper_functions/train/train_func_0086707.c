vocdusave_me(voccxdef *ctx, objnum old_me)
{
    uchar     *p;
    objucxdef *uc = ctx->voccxundo;


    if (uc == 0 || !objuok(uc))
        return;


    p = objures(uc, OBJUCLI, 3);
    *p = VOC_UNDO_SETME;
    oswp2(p+1, old_me);


    uc->objucxhead += 3;
}
