print_auto_fit_string (FitType fit, FILE *fp)
{
    if (fit == PLOT_FIT_OLS) {
	fputs("# plot includes automatic fit: OLS\n", fp);
    } else if (fit == PLOT_FIT_QUADRATIC) {
	fputs("# plot includes automatic fit: quadratic\n", fp);
    } else if (fit == PLOT_FIT_CUBIC) {
	fputs("# plot includes automatic fit: cubic\n", fp);
    } else if (fit == PLOT_FIT_INVERSE) {
	fputs("# plot includes automatic fit: inverse\n", fp);
    } else if (fit == PLOT_FIT_LOESS) {
	fputs("# plot includes automatic fit: loess\n", fp);
    } else if (fit == PLOT_FIT_LOGLIN) {
	fputs("# plot includes automatic fit: semilog\n", fp);
    }
}
