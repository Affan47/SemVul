giraffe_wlcalibration_config_destroy(GiWCalConfig *config)
{

    if (config) {
        if (config->line_widths) {
            cx_free(config->line_widths);
        }

        if (config->line_wlrange) {
            giraffe_range_delete(config->line_wlrange);
        }

        if (config->line_model) {
            cx_free(config->line_model);
        }

        if (config->line_residuals) {
            cx_free(config->line_residuals);
        }

        if (config->opt_model) {
            cx_free(config->opt_model);
        }

        cx_free(config);
    }

    return;

}
