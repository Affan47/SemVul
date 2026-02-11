entangle_control_range_new(const char *path,
                                                 int id,
                                                 const char *label,
                                                 const char *info,
                                                 gboolean readonly,
                                                 float min,
                                                 float max,
                                                 float step)
{
    g_return_val_if_fail(path != NULL, NULL);
    g_return_val_if_fail(label != NULL, NULL);

    return ENTANGLE_CONTROL_RANGE(g_object_new(ENTANGLE_TYPE_CONTROL_RANGE,
                                               "path", path,
                                               "id", id,
                                               "label", label,
                                               "info", info,
                                               "readonly", readonly,
                                               "range-min", min,
                                               "range-max", max,
                                               "range-step", step,
                                               NULL));
}
