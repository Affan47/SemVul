epr_copy_field_elems_as_uints(const EPR_SField* field, uint* buffer, uint num_elems)
{
    uint num_elems_min = 0;
    uint i;

    epr_clear_err();

    if (field == NULL) {
        epr_set_err(e_err_invalid_field_name,
                    "epr_copy_field_elems_as_uints: invalid field name");
        return num_elems_min;
    }

    num_elems_min = num_elems;
    if (field->info->num_elems < num_elems_min) {
        num_elems_min = field->info->num_elems;
    }

    if (field->info->data_type_id == e_tid_uchar) {
        for (i = 0; i < num_elems_min; i++) {
            buffer[i] = (uint)((uchar*) field->elems)[i];
        }
    } else if (field->info->data_type_id == e_tid_char) {
        for (i = 0; i < num_elems_min; i++) {
            buffer[i] = (uint)((char*) field->elems)[i];
        }
    } else if (field->info->data_type_id == e_tid_ushort) {
        for (i = 0; i < num_elems_min; i++) {
            buffer[i] = (uint)((ushort*) field->elems)[i];
        }
    } else if (field->info->data_type_id == e_tid_short) {
        for (i = 0; i < num_elems_min; i++) {
            buffer[i] = (uint)((short*) field->elems)[i];
        }
    } else if (field->info->data_type_id == e_tid_int) {
        for (i = 0; i < num_elems_min; i++) {
            buffer[i] = (uint)((uint*) field->elems)[i];
        }
    } else {
        epr_set_err(e_err_invalid_data_format,
                    "epr_copy_field_elems_as_uints: invalid type");
        return 0;
    }

    return num_elems_min;
}
