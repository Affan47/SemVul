IterSetIterCount (Iter it, int num)
{
    register int i;

    if (it->allow_expansion)
    {
        it->max_count = num;
        it->allow_expansion = False;
        return FmSuccess;
    }


    if (it->max_count == 0)
        return FmNoMoreData;


    switch (it->template->type)
    {
    case ITER:
        for (i = 0;  i < it->max_count;  i++)
        {
            ExtraData d;
            ExtraDataRec dr;

            if ((d = ChainMgrGetExtraData(&it->cm, i)) == NULL)
            {
                dr.iter = IterInit(it->template + 1, num);
                (void)ChainMgrSetData(&it->cm, i, dr);
                return FmSuccess;
            }

            if (IterSetIterCount(d->iter, num) == FmSuccess)
                return FmSuccess;

        }

        if (it->allow_expansion)
        {
            ExtraDataRec dr;

            dr.iter = IterInit (it->template + 1, num);
            ChainMgrSetData (&it->cm, it->max_count, dr);
            it->max_count++;

            return FmSuccess;
        }

        break;

    case POINTER:
        for (i = 0;  i < it->max_count;  i++)
        {
            ExtraData d;
            ExtraDataRec dr;

            if ((d = ChainMgrGetExtraData (&it->cm, i)) == NULL)
            {
                dr.fi = FrameInstInit (it->template[1].data);
                d = ChainMgrSetData (&it->cm, i, dr);
            }

            if (FrameInstSetIterCount (d->fi, num) == FmSuccess)
                return FmSuccess;

        }

        if (it->allow_expansion)
        {
            ExtraDataRec dr;

            dr.fi = FrameInstInit (it->template[1].data);
            ChainMgrSetData (&it->cm, it->max_count, dr);
            it->max_count++;

            if (FrameInstSetIterCount (dr.fi, num) == FmSuccess)
                return FmSuccess;

        }

        break;

    default:
	break;
    }

    return FmNoMoreData;
}
