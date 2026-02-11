HUF_fix_trigger(pTHX_ SV *trigger, SV *new_id) {
    AV* cont = HUF_get_trigger_content(aTHX_ trigger);
    HV* field_tab = (HV*) *av_fetch(cont, 1, 0);
    HV* new_tab = newHV();
    HE* ent;
    SV* old_id = *av_fetch(cont, 0, 0);
    hv_iterinit(field_tab);
    while ((ent = hv_iternext(field_tab))) {
        SV* field_ref = HeVAL(ent);
        HV* field = (HV*)SvRV(field_ref);
        UV field_addr = PTR2UV(field);
        SV* val;

        (void) hv_store(new_tab, (char *)&field_addr, sizeof(field_addr), SvREFCNT_inc(field_ref), 0);

        if ((val = hv_delete_ent(field, old_id, 0, 0)))
            (void) hv_store_ent(field, new_id, SvREFCNT_inc(val), 0);
    }

    av_store(cont, 0, SvREFCNT_inc(new_id));
    av_store(cont, 1, (SV*)new_tab);
}
