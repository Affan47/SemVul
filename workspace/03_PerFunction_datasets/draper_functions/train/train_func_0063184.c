ui_series_unref(ui_series_t * ui_series) {

  GList * temp_objects;
  gboolean return_val;
  gint i;

  g_return_val_if_fail(ui_series != NULL, NULL);


  g_return_val_if_fail(ui_series->reference_count > 0, NULL);


  ui_series->reference_count--;


  if (ui_series->reference_count == 0) {
#ifdef AMIDE_DEBUG
    g_print("freeing ui_series\n");
#endif
    if (ui_series->idle_handler_id != 0) {
      g_source_remove(ui_series->idle_handler_id);
      ui_series->idle_handler_id = 0;
    }

    if (ui_series->active_ds != NULL)
      ui_series->active_ds = amitk_object_unref(ui_series->active_ds);

    if (ui_series->objects != NULL) {


      temp_objects = ui_series->objects;
      while (temp_objects != NULL) {
	if (AMITK_IS_DATA_SET(temp_objects->data)) {
	  g_signal_handlers_disconnect_by_func(G_OBJECT(temp_objects->data),
					       G_CALLBACK(data_set_invalidate_slice_cache), ui_series);
	  g_signal_handlers_disconnect_by_func(G_OBJECT(temp_objects->data),
					       G_CALLBACK(color_table_changed_cb), ui_series);
	}
	g_signal_handlers_disconnect_by_func(G_OBJECT(temp_objects->data),
					     G_CALLBACK(changed_cb), ui_series);

	temp_objects = temp_objects->next;
      }
      amitk_objects_unref(ui_series->objects);
      ui_series->objects = NULL;
    }

    if (ui_series->slice_cache != NULL) {
      ui_series->slice_cache = amitk_objects_unref(ui_series->slice_cache);
    }

    if (ui_series->volume != NULL) {
      amitk_object_unref(ui_series->volume);
      ui_series->volume = NULL;
    }

    if (ui_series->thresholds_dialog != NULL) {
      gtk_widget_destroy(ui_series->thresholds_dialog);
      ui_series->thresholds_dialog = NULL;
    }

    if (ui_series->preferences != NULL) {
      g_object_unref(ui_series->preferences);
      ui_series->preferences = NULL;
    }

    if (ui_series->progress_dialog != NULL) {
      g_signal_emit_by_name(G_OBJECT(ui_series->progress_dialog), "delete_event", NULL, &return_val);
      ui_series->progress_dialog = NULL;
    }

    if (ui_series->images != NULL) {
      g_free(ui_series->images);
      ui_series->images = NULL;
    }

    if (ui_series->captions != NULL) {
      g_free(ui_series->captions);
      ui_series->captions = NULL;
    }

    if (ui_series->items != NULL) {
      for (i=0; i < ui_series->num_slices; i++) {
	if (ui_series->items[i] != NULL) {
	  g_list_free(ui_series->items[i]);
	  ui_series->items[i] = NULL;
	}
      }
      g_free(ui_series->items);
      ui_series->items = NULL;
    }

    if (ui_series->frame_durations != NULL) {
      g_free(ui_series->frame_durations);
      ui_series->frame_durations = NULL;
    }

    g_free(ui_series);
    ui_series = NULL;
  }

  return ui_series;

}
