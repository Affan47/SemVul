search_gui_update_items_label(const struct search *search)
{
	if (search != current_search)
		return;

    if (search) {
		gtk_label_printf(label_items_found, _("%u %s "
			"(%u skipped, %u ignored, %u hidden, %u auto-d/l, %u %s)"
			" Hits: %u (%u TCP, %u UDP)"),
			search->items, NG_("item", "items", search->items),
			search->skipped,
			search->ignored,
			search->hidden,
			search->auto_downloaded,
			search->duplicates, NG_("dupe", "dupes", search->duplicates),
			search->tcp_qhits + search->udp_qhits,
			search->tcp_qhits,
			search->udp_qhits);
    } else {
       gtk_label_printf(label_items_found, "%s", _("No search"));
	}
}
