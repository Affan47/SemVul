get_random_query_type (void)
{
    switch (get_random_int_in_range (0, 4))
    {
    case 0:
        return SIMPLE_QT;
    case 1:
        return SPLIT_KVP_QT;
    case 2:
        return TRANS_KVP_QT;
    case 3:
        return ACCOUNT_KVP_QT;
    case 4:
        return GUID_QT;
    default:
        return SIMPLE_QT;
    }
}
