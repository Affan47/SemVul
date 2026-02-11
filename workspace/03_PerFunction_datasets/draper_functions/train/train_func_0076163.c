enroll_data_destroy (EnrollData *data)
{
        switch (data->state) {
        case STATE_ENROLLING:
                enroll_stop (data, NULL);

        case STATE_CLAIMED:
                release (data, NULL);

        case STATE_NONE:
                g_free (data->name);
                g_object_unref (data->device);
                g_object_unref (data->dialog);
                gtk_widget_destroy (data->ass);

                g_free (data);
        }
}
