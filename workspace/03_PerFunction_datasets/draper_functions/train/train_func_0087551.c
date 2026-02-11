ossl_ec_group_set_point_conversion_form(VALUE self, VALUE form_v)
{
    EC_GROUP *group = NULL;
    point_conversion_form_t form;
    ID form_id = SYM2ID(form_v);

    Require_EC_GROUP(self, group);

    if (form_id == ID_uncompressed) {
        form = POINT_CONVERSION_UNCOMPRESSED;
    } else if (form_id == ID_compressed) {
        form = POINT_CONVERSION_COMPRESSED;
    } else if (form_id == ID_hybrid) {
        form = POINT_CONVERSION_HYBRID;
    } else {
        ossl_raise(rb_eArgError, "form must be :compressed, :uncompressed, or :hybrid");
    }

    EC_GROUP_set_point_conversion_form(group, form);

    return form_v;
}
