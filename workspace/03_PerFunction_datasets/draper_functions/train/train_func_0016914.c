text_editor_find (TextEditor * te, const gchar * str, gint scope,
				  gboolean forward, gboolean regexp,
				  gboolean ignore_case, gboolean whole_word, gboolean wrap)
{
	glong ret;
	GtkWidget *editor;
	glong flags;
	int current_pos, current_anchor;

	if (!te) return -1;
	editor = te->scintilla;

	flags = (ignore_case ? 0 : SCFIND_MATCHCASE)
		| (regexp ? SCFIND_REGEXP : 0)
		| (whole_word ? SCFIND_WHOLEWORD : 0)
		| (forward ? 0 : ANEFIND_REVERSE_FLAG);

	switch (scope)
	{
		case TEXT_EDITOR_FIND_SCOPE_WHOLE:
				if (forward)
				{
					scintilla_send_message (SCINTILLA (editor), SCI_SETANCHOR,
											0, 0);
					scintilla_send_message (SCINTILLA (editor),
											SCI_SETCURRENTPOS, 0, 0);
				}
				else
				{
					glong length;
					length = scintilla_send_message (SCINTILLA (editor),
													 SCI_GETTEXTLENGTH, 0, 0);
					scintilla_send_message (SCINTILLA (editor),
											SCI_SETCURRENTPOS, length-1, 0);
					scintilla_send_message (SCINTILLA (editor),
											SCI_SETANCHOR, length-1, 0);
				}
			break;
		default:
			break;
	}
	current_pos = scintilla_send_message (SCINTILLA (editor),
										  SCI_GETCURRENTPOS, 0, 0);
	current_anchor = scintilla_send_message (SCINTILLA (editor),
											 SCI_GETANCHOR, 0, 0);
	ret = aneditor_command (te->editor_id, ANE_FIND, flags, (long)str);
	if (scope == TEXT_EDITOR_FIND_SCOPE_CURRENT && wrap && ret < 0) {

		if (forward)
		{
			scintilla_send_message (SCINTILLA (editor), SCI_SETANCHOR, 0, 0);
			scintilla_send_message (SCINTILLA (editor), SCI_SETCURRENTPOS,
									0, 0);
		}
		else
		{
			glong length;
			length = scintilla_send_message (SCINTILLA (editor),
											 SCI_GETTEXTLENGTH, 0, 0);
			scintilla_send_message (SCINTILLA (editor), SCI_SETCURRENTPOS,
									length-1, 0);
			scintilla_send_message (SCINTILLA (editor), SCI_SETANCHOR,
									length-1, 0);
		}
		ret = aneditor_command (te->editor_id, ANE_FIND, flags, (long)str);

		if (ret < 0) {
			scintilla_send_message (SCINTILLA (editor), SCI_SETANCHOR,
									current_anchor, 0);
			scintilla_send_message (SCINTILLA (editor), SCI_SETCURRENTPOS,
									current_pos, 0);
		}
	}
	return ret;
}
