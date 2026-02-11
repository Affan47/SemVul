k5_json_bool_create(int truth, k5_json_bool *val_out)
{
    k5_json_bool b;

    *val_out = NULL;
    b = alloc_value(&bool_type, 1);
    if (b == NULL)
        return ENOMEM;
    *(unsigned char *)b = !!truth;
    *val_out = b;
    return 0;
}
