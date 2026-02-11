test_recording (Fixture *fixture, gconstpointer data)
{
    GError *error = NULL;
    UcaCamera *camera = UCA_CAMERA (fixture->camera);

    uca_camera_stop_recording (camera, &error);
    g_assert_error (error, UCA_CAMERA_ERROR, UCA_CAMERA_ERROR_NOT_RECORDING);
    g_error_free (error);

    error = NULL;
    uca_camera_start_recording (camera, &error);
    g_assert_no_error (error);
    uca_camera_stop_recording (camera, &error);
    g_assert_no_error (error);
}
