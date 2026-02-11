GetCardAttribute (char *rec, XICAttribute *list, int need_swap)
{
    FrameMgr fm;
    unsigned char *recp = (unsigned char *) rec;

    GetAttrHeader (recp, list, need_swap);
    recp += sizeof (CARD16)*2;

    if (list->value_length == sizeof (CARD8))
    {
        memmove (recp, list->value, list->value_length);
    }
    else if (list->value_length == sizeof (CARD16))
    {
        INT16 *value = (INT16 *) list->value;
        extern XimFrameRec short_fr[];

        fm = FrameMgrInit (short_fr, (char *) recp, need_swap);

        FrameMgrPutToken (fm, *value);
        FrameMgrFree (fm);
    }
    else if (list->value_length == sizeof (CARD32))
    {
        INT32 *value = (INT32 *) list->value;
        extern XimFrameRec long_fr[];

        fm = FrameMgrInit (long_fr, (char *) recp, need_swap);

        FrameMgrPutToken (fm, *value);
        FrameMgrFree (fm);
    }

}
