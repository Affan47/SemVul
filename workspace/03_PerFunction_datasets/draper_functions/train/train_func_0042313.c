free_block_array_info(Block *block_head)
{
    Block *block;

    for (block = block_head;
         block != NULL;
         block = block->next) {

        free_block_array_info(block->inner);

        if (block->array_info != NULL) {
            free_all_array_def_use_table_semnode(
                block->array_info->MayUse);
            block->array_info->MayUse = NULL;

            free_all_array_def_use_table_semnode(
                block->array_info->MayMod);
            block->array_info->MayMod = NULL;

            free_all_array_def_use_table_semnode(
                block->array_info->ExposedUse);
            block->array_info->ExposedUse = NULL;

            free_all_array_def_use_table_semnode(
                block->array_info->Kill);
            block->array_info->Kill = NULL;

            free_all_array_def_use_table_semnode(
                block->array_info->In);
            block->array_info->In = NULL;

            free_all_array_def_use_table_semnode(
                block->array_info->Out);
            block->array_info->Out = NULL;

            free_all_array_def_use_table_semnode(
                block->array_info->Consumption);
            block->array_info->Consumption = NULL;

            free_all_array_def_use_table_semnode(
                block->array_info->Production);
            block->array_info->Production = NULL;
        }
    }

    return;
}
