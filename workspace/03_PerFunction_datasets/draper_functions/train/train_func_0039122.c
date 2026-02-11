test_recording_signal (Fixture *fixture, gconstpointer data)
{
    UcaCamera *camera = UCA_CAMERA (fixture->camera);
    gboolean success = FALSE;
    g_signal_connect (G_OBJECT (camera), "notify::is-recording",
            (GCallback) on_property_change, &success);

    uca_camera_start_recording (camera, NULL);
    g_assert (success == TRUE);

    success = FALSE;
    uca_camera_stop_recording (camera, NULL);
    g_assert (success == TRUE);
}
