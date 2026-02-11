markers_remove_breakpoint(breakpoint *bp)
{
	static int breakpoint_markers[] = {
		M_BP_ENABLED,
		M_BP_DISABLED,
		M_BP_CONDITIONAL
	};

	GeanyDocument *doc = document_find_by_filename(bp->file);
	if (doc)
	{
		int markers = scintilla_send_message(doc->editor->sci, SCI_MARKERGET, bp->line - 1, (long)NULL);
		int markers_count = sizeof(breakpoint_markers) / sizeof(breakpoint_markers[0]);
		int i = 0;
		for (; i < markers_count; i++)
		{
			int marker = breakpoint_markers[i];
			if (markers & (0x01 << marker))
			{
				sci_delete_marker_at_line(doc->editor->sci, bp->line - 1, marker);
			}
		}
	}
}
