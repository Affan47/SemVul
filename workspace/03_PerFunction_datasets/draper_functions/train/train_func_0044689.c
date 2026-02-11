test_runner_op_assert(int x, int line, char *file)
{
    test_runner_global_instance.test_assert++;

    if (!x) {
        test_runner_console_color(1, 1, 8);
        fprintf(
            test_runner_global_instance.outstream,
            TEST_RUNNER_MSG_ASSERT_FAILED,
            file,
            line
        );
        test_runner_console_color(0, 8, 8);

        test_runner_global_instance.case_list_current->case_failed = 1;
        test_runner_global_instance.test_fail++;
    }
}
