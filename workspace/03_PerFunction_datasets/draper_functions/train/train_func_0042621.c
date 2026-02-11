gwy_calibration_copy(gpointer item)
{
    GwyCalibration *calibration, *copy;

    g_return_val_if_fail(GWY_IS_CALIBRATION(item), NULL);

    calibration = GWY_CALIBRATION(item);
    copy = gwy_calibration_new(gwy_resource_get_name(GWY_RESOURCE(item)),
                            calibration->filename);

    return copy;
}
