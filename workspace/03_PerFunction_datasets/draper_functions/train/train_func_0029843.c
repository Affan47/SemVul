slapi_value_set_berval( Slapi_Value *value, const struct berval *bval )
{
    if(value!=NULL)
    {
        ber_bvdone(&value->bv);
        if(bval!=NULL)
        {
            ber_bvcpy(&value->bv, bval);
        }
    }
    return value;
}
