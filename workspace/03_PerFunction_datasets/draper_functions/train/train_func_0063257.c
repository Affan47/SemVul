update_status (TestRowInfo *info, CutTestResultStatus status)
{
    TestCaseRowInfo *test_case_row_info;
    CutGtkUI *ui;

    info->status = status;
    test_case_row_info = info->test_case_row_info;
    ui = test_case_row_info->ui;

    if (test_case_row_info->status < status)
        test_case_row_info->status = status;

    if (ui->status < status)
        ui->status = status;
}
