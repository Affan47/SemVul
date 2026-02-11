find_grain_value_by_quantity(G_GNUC_UNUSED gpointer key,
                             gpointer value,
                             gpointer user_data)
{
    GwyGrainValue *gvalue = (GwyGrainValue*)value;

    return (gvalue->data.group != GWY_GRAIN_VALUE_GROUP_USER
            && gvalue->builtin == GPOINTER_TO_UINT(user_data));
}
