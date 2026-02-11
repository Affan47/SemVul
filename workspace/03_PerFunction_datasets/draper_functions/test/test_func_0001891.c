FrameInstIsIterLoopEnd (FrameInst fi)
{
    Bool ret = False;

    if (fi->template[fi->cur_no].type == ITER)
    {
        ExtraData d = ChainMgrGetExtraData (&fi->cm, fi->cur_no);
        Bool yourself;

        if (d)
        {
            ret = IterIsLoopEnd (d->iter, &yourself);
            if (ret  &&  yourself)
                fi->cur_no = _FrameInstIncrement (fi->template, fi->cur_no);

        }

    }

    return (ret);
}
