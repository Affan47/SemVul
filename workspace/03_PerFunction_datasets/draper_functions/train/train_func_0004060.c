copy_array_info(Array_def_use_info *source, Array_def_use_info *dest)
{
    if (source != NULL && dest != NULL) {
        dest->MayUse = copy_array_def_use_table_semnode(source->MayUse);
        dest->MayMod = copy_array_def_use_table_semnode(source->MayMod);
        dest->ExposedUse = copy_array_def_use_table_semnode(source->ExposedUse);
        dest->Kill = copy_array_def_use_table_semnode(source->Kill);
        dest->Consumption = copy_array_def_use_table_semnode(source->Consumption);
        dest->Production = copy_array_def_use_table_semnode(source->Production);
    }
}
