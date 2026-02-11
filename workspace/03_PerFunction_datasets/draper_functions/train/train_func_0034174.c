assign_aa_to_slot(Block *b, Stasche_lm_dt *sld, List *head, const int level)
{
    if (cmp_ya_templ) {
        assign_aa_to_slot_template(b, sld, head, level);
    } else {
        List *ghead = NULL;
        ghead = assign_aa_to_slot_body(b, sld, head, -1, NULL, ghead, level);
        set_cmp_localize_group_info(b, head, ghead);
    }
}
