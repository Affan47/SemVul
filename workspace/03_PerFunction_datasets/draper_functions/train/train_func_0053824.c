_gconf_cleaner_question_dialog_on_response(GtkDialog *dialog,
					   gint       response_id,
					   gpointer   data)
{
	if (!quark_question_response)
		quark_question_response = g_quark_from_static_string("gconf-cleaner-question-response");

	if (response_id == GTK_RESPONSE_YES)
		g_object_set_qdata(G_OBJECT (dialog), quark_question_response, (gpointer)TRUE);
	else
		g_object_set_qdata(G_OBJECT (dialog), quark_question_response, (gpointer)FALSE);
}
