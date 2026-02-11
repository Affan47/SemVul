copy_slot_to_temp_body(Slot *slot)
{
    Cmp_localize_group_info *g = slot->group_info;
    slot->tsize = slot->size;
    if (slot->tdu != NULL) {
        free_all_array_def_use_table_semnode(slot->tdu);
        slot->tdu = NULL;
    }
    if (g != NULL) {
        slot->tdu = copy_array_def_use_table_semnode(g->local_du);
    }
}
