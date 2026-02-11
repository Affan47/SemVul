assign_array_to_slot(Array_table *atbl, const int array_size,
                     int *vslot, const int slot_size,
                     const int slot_num)
{
    int i;

    for (i = 0; i < slot_num; i++) {
        int tmp = vslot[i]
            + vslot[i] % byte2word(get_element_byte_size(atbl->type,
                                                         atbl->type_entry));
        if (tmp + array_size <= slot_size) {
            vslot[i] = tmp + array_size;
            return TRUE;
        }
    }

    return FALSE;
}
