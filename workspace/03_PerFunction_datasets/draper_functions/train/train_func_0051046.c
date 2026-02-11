ED4_sequence_changed_cb(GBDATA *gb_seq, int *cl, GB_CB_TYPE gbtype)
{
    ED4_base *base = (ED4_base*)(cl);

    if (base->get_species_pointer()!=gb_seq) {
        e4_assert(0);
        aw_message("Illegal callback (ED4_sequence_changed_cb())");
    }

    if (gbtype&GB_CB_DELETE) {
        e4_assert(gbtype==GB_CB_DELETE);
        base->deleted_from_database();
    }

    if (gbtype&GB_CB_CHANGED) {
        base->changed_by_database();
    }

    if (gbtype&GB_CB_SON_CREATED) {

    }
}
