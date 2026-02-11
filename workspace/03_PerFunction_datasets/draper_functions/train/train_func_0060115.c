handle_crash (CutRunContext  *run_context,
              CutTestResult  *result,
              CutConsoleUI   *console)
{
    if (console->verbose_level < CUT_VERBOSE_LEVEL_NORMAL)
        return;
    print_progress(console, CUT_TEST_RESULT_CRASH, "!");
    fflush(stdout);
}
