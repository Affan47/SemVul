set_display_style(GEN_DisplayStyle type) {
    style = type;

    switch (style) {
        case GEN_DISPLAY_STYLE_RADIAL: {
            exports.dont_fit_x      = 0;
            exports.dont_fit_y      = 0;
            exports.dont_fit_larger = 0;
            break;
        }
        case GEN_DISPLAY_STYLE_VERTICAL: {
            exports.dont_fit_x      = 0;
            exports.dont_fit_y      = 1;
            exports.dont_fit_larger = 0;
            break;
        }
        case GEN_DISPLAY_STYLE_BOOK: {
            exports.dont_fit_x      = 0;
            exports.dont_fit_y      = 1;
            exports.dont_fit_larger = 0;
            break;
        }
        default: {
            gen_assert(0);
            break;
        }
    }

    want_zoom_reset = true;
}
