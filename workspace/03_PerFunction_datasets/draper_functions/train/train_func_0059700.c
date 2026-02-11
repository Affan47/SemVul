close_candidate_window (GtkIMContextHangul *hic)
{
    if (hic->candidate_string != NULL && hic->candidate_string->len > 0)
	g_array_set_size(hic->candidate_string, 0);
    candidate_delete(hic->candidate);
    hic->candidate = NULL;
}
