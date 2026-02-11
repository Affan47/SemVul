exotic_summary(struct exotic_handle* handle)
{
	int total     = handle->pass + handle->fail;
	int pass_rate = total ? (100*handle->pass / total) : 0;
	int fail_rate = total ? (100*handle->fail / total) : 0;

	printf("\n");
	printf("--------------------------------------------\n");
	printf("Results:\n");
	printf(" * Total tests run:  %8d\n", total);
	printf(" * Tests passed:     %8d (~%d%%)\n", (int) handle->pass, pass_rate);
	printf(" * Tests failed:     %8d (~%d%%)\n", (int) handle->fail, fail_rate);
	printf("--------------------------------------------\n");
}
