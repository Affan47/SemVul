gtk_hex_new(HexDocument *owner) {
	GtkHex *gh;

	gh = GTK_HEX (g_object_new (GTK_TYPE_HEX, NULL));
	g_return_val_if_fail (gh != NULL, NULL);

	gh->document = owner;
    g_signal_connect (G_OBJECT (gh->document), "document_changed",
            G_CALLBACK (gtk_hex_document_changed), gh);

	return GTK_WIDGET(gh);
}
