read_reporter_results(TestReporter *reporter) {
    int completed = 0;
    int result;
    while ((result = receive_cgreen_message(reporter->ipc)) > 0) {
        if (result == pass) {
            reporter->passes++;
        } else if (result == fail) {
            reporter->failures++;
        } else if (result == completion) {
            completed = 1;
        }
    }
    if (! completed) {
        (*reporter->show_incomplete)(reporter, get_current_from_breadcrumb((CgreenBreadcrumb *)reporter->breadcrumb));
        reporter->exceptions++;
    }
}
