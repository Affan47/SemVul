_getVariant(const struct uuid &uuid)
{

    UT_sint32 var = uuid.clock_seq;

    if ((var & 0x8000) == 0)
        return UT_UUID_VARIANT_NCS;
    if ((var & 0x4000) == 0)
        return UT_UUID_VARIANT_DCE;
    if ((var & 0x2000) == 0)
        return UT_UUID_VARIANT_MICROSOFT;
    return UT_UUID_VARIANT_OTHER;
}
