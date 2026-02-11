pgd_attachments_validate_button_clicked (GtkButton   *button,
					 GtkTreeView *treeview)
{
	GtkTreeSelection  *selection;
	GtkTreeModel      *model;
	GtkTreeIter        iter;
	GChecksum         *cs;
	guint8            *digest;
	gsize              digest_len;
	PopplerAttachment *attachment;
	gboolean           valid = TRUE;

	selection = gtk_tree_view_get_selection (treeview);
	if (!gtk_tree_selection_get_selected (selection, &model, &iter))
		return;

	gtk_tree_model_get (model, &iter,
			    ATTACHMENTS_ATTACHMENT_COLUMN, &attachment,
			    -1);

	if (!attachment)
		return;

	if (attachment->checksum->len == 0) {
		message_dialog_run (GTK_WINDOW (gtk_widget_get_toplevel (GTK_WIDGET (treeview))),
				    "Impossible to validate attachment: checksum is not available");
		g_object_unref (attachment);

		return;
	}

	cs = g_checksum_new (G_CHECKSUM_MD5);
	poppler_attachment_save_to_callback (attachment, attachment_save_callback,
					     (gpointer)cs, NULL);
	digest_len = g_checksum_type_get_length (G_CHECKSUM_MD5);
	digest = (guint8 *) g_malloc (digest_len);
	g_checksum_get_digest (cs, digest, &digest_len);
	g_checksum_free (cs);

	if (attachment->checksum->len == digest_len) {
		gint i;

		for (i = 0; i < digest_len; i++) {
			if ((guint8)attachment->checksum->str[i] != digest[i]) {
				valid = FALSE;
				break;
			}
		}
	}

	if (valid) {
		message_dialog_run (GTK_WINDOW (gtk_widget_get_toplevel (GTK_WIDGET (treeview))),
				    "Attachment is valid");
	} else {
		message_dialog_run (GTK_WINDOW (gtk_widget_get_toplevel (GTK_WIDGET (treeview))),
				    "Attachment is not valid: the checksum does not match");
	}

	g_free (digest);
	g_object_unref (attachment);
}
