gpk_application_progress_cb (PkProgress *progress, PkProgressType type, GpkApplicationPrivate *priv)
{
	PkStatusEnum status;
	gint percentage;
	gboolean allow_cancel;
	GtkWidget *widget;

	g_object_get (progress,
		      "status", &status,
		      "percentage", &percentage,
		      "allow-cancel", &allow_cancel,
		      NULL);

	if (type == PK_PROGRESS_TYPE_STATUS) {
		g_debug ("now %s", pk_status_enum_to_string (status));

		if (status == PK_STATUS_ENUM_FINISHED) {

			widget = GTK_WIDGET (gtk_builder_get_object (priv->builder, "treeview_packages"));
			gtk_widget_set_sensitive (widget, TRUE);


			widget = GTK_WIDGET (gtk_builder_get_object (priv->builder, "button_cancel"));
			gtk_widget_hide (widget);


			widget = GTK_WIDGET (gtk_builder_get_object (priv->builder, "button_apply"));
			gtk_widget_set_sensitive (widget, TRUE);


			if (priv->status_id > 0) {
				g_source_remove (priv->status_id);
				priv->status_id = 0;
			}

			widget = GTK_WIDGET (gtk_builder_get_object (priv->builder, "label_status"));
			gtk_widget_hide (widget);
			widget = GTK_WIDGET (gtk_builder_get_object (priv->builder, "progressbar_progress"));
			gtk_widget_hide (widget);
			goto out;
		}


		if (priv->status_id > 0)
			goto out;


		priv->status_id =
			g_timeout_add (GPK_UI_STATUS_SHOW_DELAY,
				       (GSourceFunc) gpk_application_status_changed_timeout_cb,
				       priv);
		g_source_set_name_by_id (priv->status_id,
					 "[GpkApplication] status-changed");


		priv->status_last = status;

	} else if (type == PK_PROGRESS_TYPE_PERCENTAGE) {
		widget = GTK_WIDGET (gtk_builder_get_object (priv->builder, "progressbar_progress"));
		if (percentage > 0) {
			gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (widget), (gfloat) percentage / 100.0f);
		} else {
			gtk_widget_hide (widget);
		}

	} else if (type == PK_PROGRESS_TYPE_ALLOW_CANCEL) {
		widget = GTK_WIDGET (gtk_builder_get_object (priv->builder, "button_cancel"));
		gtk_widget_set_sensitive (widget, allow_cancel);
	}
out:
	return;
}
