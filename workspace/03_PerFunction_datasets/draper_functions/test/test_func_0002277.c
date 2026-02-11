gcr_import_button_clicked (GtkButton *button)
{
	GcrImportButton *self = GCR_IMPORT_BUTTON (button);

	g_return_if_fail (self->pv->importing == FALSE);
	g_return_if_fail (self->pv->importers != NULL);


	if (self->pv->importers->next) {
		update_importer_menu (self);
		gtk_menu_popup (self->pv->menu, NULL, NULL, on_menu_position,
		                self, 1, gtk_get_current_event_time ());


	} else {
		begin_import (self, self->pv->importers->data);
	}

	update_import_button (self);
}
