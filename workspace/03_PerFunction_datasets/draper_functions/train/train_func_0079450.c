epr_get_field_elem_as_double(const EPR_SField* field, uint elem_index)
{
    epr_clear_err();

    if (field == NULL) {
        epr_set_err(e_err_invalid_field_name,
                    "epr_get_field_elems_as_double: invalid field name");
        return 0.0;

    }
    if (elem_index >= field->info->num_elems) {
        epr_set_err(e_err_invalid_value,
                    "epr_get_field_elems_as_double: invalid elem_index parameter");
        return 0.0;
    }

    if (field->info->data_type_id == e_tid_double) {
        return (double)((double*) field->elems)[elem_index];
    }
    if (field->info->data_type_id == e_tid_float) {
        return (double)((float*) field->elems)[elem_index];
    }
    if (field->info->data_type_id == e_tid_uchar) {
        return (double)((uchar*) field->elems)[elem_index];
    }
    if (field->info->data_type_id == e_tid_char) {
        return (double)((char*) field->elems)[elem_index];
    }
    if (field->info->data_type_id == e_tid_ushort) {
        return (double)((ushort*) field->elems)[elem_index];
    }
    if (field->info->data_type_id == e_tid_short) {
        return (double)((short*) field->elems)[elem_index];
    }
    if (field->info->data_type_id == e_tid_uint) {
        return (double)((uint*) field->elems)[elem_index];
    }
    if (field->info->data_type_id == e_tid_int) {
        return (double)((int*) field->elems)[elem_index];
    }

    epr_set_err(e_err_invalid_data_format,
                "epr_get_field_elems_as_double: invalid type");

    return 0.0;
}
