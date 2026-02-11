gnc_ab_get_account_kvp(const Account *a, gboolean create)
{
    kvp_frame *toplevel = xaccAccountGetSlots(a);
    kvp_frame *result = kvp_frame_get_frame(toplevel, AB_KEY);
    if (!result && create)
    {
        result = kvp_frame_new();
        kvp_frame_add_frame_nc(toplevel, AB_KEY, result);
    }
    return result;
}
