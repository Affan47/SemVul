gnc_split_register_get_parent (SplitRegister *reg)
{
    SRInfo *info = gnc_split_register_get_info (reg);

    if (reg == NULL)
        return NULL;

    if (info->get_parent == NULL)
        return NULL;

    return info->get_parent (info->user_data);
}
