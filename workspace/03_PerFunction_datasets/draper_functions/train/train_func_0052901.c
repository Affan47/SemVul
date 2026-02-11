SetCardAttribute (XICAttribute *value_ret,
                              char *p,
                              XICAttr *ic_attr,
                              int value_length,
                              int need_swap,
                              void **value_buf)
{
    FrameMgr fm;


    if (value_length == sizeof (CARD8))
    {
        memmove (*value_buf, p, value_length);
    }
    else if (value_length == sizeof (CARD16))
    {
        INT16 value;
        extern XimFrameRec short_fr[];

        fm = FrameMgrInit (short_fr, (char *) p, need_swap);

        FrameMgrGetToken (fm, value);
        FrameMgrFree (fm);
        memmove (*value_buf, &value, value_length);
    }
    else if (value_length == sizeof(CARD32))
    {
        INT32 value;
        extern XimFrameRec long_fr[];

        fm = FrameMgrInit (long_fr, (char *) p, need_swap);

        FrameMgrGetToken (fm, value);
        FrameMgrFree (fm);
        memmove (*value_buf, &value, value_length);
    }

    value_ret->attribute_id = ic_attr->attribute_id;
    value_ret->name = ic_attr->name;
    value_ret->name_length = ic_attr->length;
    value_ret->type = ic_attr->type;
    value_ret->value_length = value_length;
    value_ret->value = *value_buf;

    *value_buf += value_length;
}
