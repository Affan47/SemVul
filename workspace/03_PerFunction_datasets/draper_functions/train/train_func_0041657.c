cb_ready_test_suite (CutRunContext *run_context, CutTestSuite *test_suite,
                     guint n_test_cases, guint n_tests,
                     CutPDFReport *report)
{
    const gchar *filename;
    cairo_surface_t *surface;

    filename = cut_report_get_filename(CUT_REPORT(report));
    if (!filename)
        return;

    if (report->context) {
        cairo_destroy(report->context);
        report->context = NULL;
    }

    surface = cairo_pdf_surface_create(filename, A4_WIDTH, A4_HEIGHT);
    report->context = cairo_create(surface);
    cairo_surface_destroy(surface);

    init_page(report->context);
}
