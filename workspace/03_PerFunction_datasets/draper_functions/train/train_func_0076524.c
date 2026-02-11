set_boxplot()
{
    c_token++;
    if (END_OF_COMMAND) {
	boxplot_style defstyle = DEFAULT_BOXPLOT_STYLE;
	boxplot_opts = defstyle;
    }
    while (!END_OF_COMMAND) {
	if (almost_equals(c_token, "noout$liers")) {
	    boxplot_opts.outliers = FALSE;
	    c_token++;
	}
	else if (almost_equals(c_token, "out$liers")) {
	    boxplot_opts.outliers = TRUE;
	    c_token++;
	}
	else if (almost_equals(c_token, "point$type") || equals (c_token, "pt")) {
	    c_token++;
	    boxplot_opts.pointtype = int_expression()-1;
	}
	else if (equals(c_token,"range")) {
	    c_token++;
	    boxplot_opts.limit_type = 0;
	    boxplot_opts.limit_value = real_expression();
	}
	else if (almost_equals(c_token,"frac$tion")) {
	    c_token++;
	    boxplot_opts.limit_value = real_expression();
	    if (boxplot_opts.limit_value < 0 || boxplot_opts.limit_value > 1)
		int_error(c_token-1,"fraction must be less than 1");
	    boxplot_opts.limit_type = 1;
	}
	else if (almost_equals(c_token,"candle$sticks")) {
	    c_token++;
	    boxplot_opts.plotstyle = CANDLESTICKS;
	}
	else if (almost_equals(c_token,"finance$bars")) {
	    c_token++;
	    boxplot_opts.plotstyle = FINANCEBARS;
	}
	else if (almost_equals(c_token,"sep$aration")) {
	    c_token++;
	    boxplot_opts.separation = real_expression();
	    if (boxplot_opts.separation < 0)
		int_error(c_token-1,"separation must be > 0");
	}
	else if (almost_equals(c_token,"lab$els")) {
	    c_token++;
	    if (equals(c_token, "off")) {
		boxplot_opts.labels = BOXPLOT_FACTOR_LABELS_OFF;
	    }
	    else if (equals(c_token, "x")) {
		boxplot_opts.labels = BOXPLOT_FACTOR_LABELS_X;
	    }
	    else if (equals(c_token, "x2")) {
		boxplot_opts.labels = BOXPLOT_FACTOR_LABELS_X2;
	    }
	    else if (equals(c_token, "auto")) {
		boxplot_opts.labels = BOXPLOT_FACTOR_LABELS_AUTO;
	    }
	    else
		int_error(c_token-1,"expecting 'x', 'x2', 'auto' or 'off'");
	    c_token++;
	}
	else if (almost_equals(c_token, "so$rted")) {
	    boxplot_opts.sort_factors = TRUE;
	    c_token++;
	}
	else if (almost_equals(c_token, "un$sorted")) {
	    boxplot_opts.sort_factors = FALSE;
	    c_token++;
	}
	else
	    int_error(c_token,"unrecognized option");
    }

}
