tracker_toc_free (TrackerToc *toc)
{
	TrackerTocEntry *entry;
	GList *n;

	if (!toc) {
		return;
	}

	for (n = toc->entry_list; n != NULL; n = n->next) {
		entry = n->data;
		gst_tag_list_free (entry->tag_list);
		g_slice_free (TrackerTocEntry, entry);
	}

	g_list_free (toc->entry_list);

	g_slice_free (TrackerToc, toc);
}
