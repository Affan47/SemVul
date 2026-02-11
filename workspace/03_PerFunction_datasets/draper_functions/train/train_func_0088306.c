select_all()
{

	if( gtk_notebook_get_current_page(GTK_NOTEBOOK(NoteBookText))==0)
		gabedit_text_select_all(text);
	else
		gabedit_text_select_all(textresult);
}
