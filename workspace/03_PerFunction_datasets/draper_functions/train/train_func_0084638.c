gnc_commodity_set_user_symbol(gnc_commodity * cm, const char * user_symbol)
{
    if (!cm) return;

    ENTER ("(cm=%p, symbol=%s)", cm, user_symbol ? user_symbol : "(null)");

    gnc_commodity_begin_edit(cm);
    kvp_frame_set_string(cm->inst.kvp_data, "user_symbol", user_symbol);
    mark_commodity_dirty(cm);
    gnc_commodity_commit_edit(cm);

    LEAVE(" ");
}
