add_calibration(GwyDataField *dfield,
                GwyContainer *data,
                gint id,
                GwyCCViewDisplayType type)
{
    gchar key[24];


    if (type == GWY_CC_VIEW_DISPLAY_X_CORR)
       g_snprintf(key, sizeof(key), "/%d/data/cal_xerr", id);
    else if (type == GWY_CC_VIEW_DISPLAY_Y_CORR)
       g_snprintf(key, sizeof(key), "/%d/data/cal_yerr", id);
    else if (type == GWY_CC_VIEW_DISPLAY_Z_CORR)
       g_snprintf(key, sizeof(key), "/%d/data/cal_zerr", id);
    else if (type == GWY_CC_VIEW_DISPLAY_X_UNC)
       g_snprintf(key, sizeof(key), "/%d/data/cal_xunc", id);
    else if (type == GWY_CC_VIEW_DISPLAY_Y_UNC)
       g_snprintf(key, sizeof(key), "/%d/data/cal_yunc", id);
    else if (type == GWY_CC_VIEW_DISPLAY_Z_UNC)
       g_snprintf(key, sizeof(key), "/%d/data/cal_zunc", id);
    else {
        g_critical("No such calibration key.");
        return;
    }
    gwy_container_set_object_by_name(data, key, dfield);

}
