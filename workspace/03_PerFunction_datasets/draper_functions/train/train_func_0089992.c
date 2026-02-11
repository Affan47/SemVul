backup_array_info_block(Block *block_head)
{
    Block *bpt;
    for (bpt = block_head; bpt != NULL; bpt = bpt->next) {
        if (bpt->inner != NULL) {
            backup_array_info_block(bpt->inner);
        }

        if (bpt->array_info != NULL) {
            bpt->array_info->block_MayUse = bpt->array_info->MayUse;
            bpt->array_info->MayUse = NULL;
            bpt->array_info->block_MayMod = bpt->array_info->MayMod;
            bpt->array_info->MayMod = NULL;
            bpt->array_info->block_ExposedUse = bpt->array_info->ExposedUse;
            bpt->array_info->ExposedUse = NULL;
            bpt->array_info->block_Kill = bpt->array_info->Kill;
            bpt->array_info->Kill = NULL;
        }
    }
}
