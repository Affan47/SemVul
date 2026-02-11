dxaccAccountGetQuoteTZ(const Account *acc)
{
    if (!acc) return NULL;

    if (xaccAccountIsPriced(acc))
    {
        KvpValue *value = kvp_frame_get_slot(acc->inst.kvp_data, "old-quote-tz");
        if (value) return (kvp_value_get_string(value));
    }
    return NULL;
}
