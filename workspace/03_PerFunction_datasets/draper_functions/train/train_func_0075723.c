replace_scalar_array_def_use_info(Block *bpt, int before, int after, symbol_kind kind)
{
    Array_def_use_info *array_info = bpt->array_info;

    if( array_info == NULL)
        return;

    if( array_info->MayUse)
        replace_scalar_array_def_use_table_semnode(array_info->MayUse, before,
                                                   after, kind);
    if( array_info->MayMod)
        replace_scalar_array_def_use_table_semnode(array_info->MayMod, before,
                                                   after, kind);
    if( array_info->ExposedUse)
        replace_scalar_array_def_use_table_semnode(array_info->ExposedUse,
                                                   before, after, kind);
    if( array_info->Kill)
        replace_scalar_array_def_use_table_semnode(array_info->Kill, before,
                                                   after, kind);
    if( array_info->In)
        replace_scalar_array_def_use_table_semnode(array_info->In, before,
                                                   after, kind);
    if( array_info->Out)
        replace_scalar_array_def_use_table_semnode(array_info->Out, before,
                                                   after, kind);
    if( array_info->Consumption)
        replace_scalar_array_def_use_table_semnode(array_info->Consumption,
                                                   before, after, kind);
    if( array_info->Production)
        replace_scalar_array_def_use_table_semnode(array_info->Production,
                                                   before, after, kind);
}
