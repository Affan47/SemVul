netbench_printer_print(
	struct linked_list *processes,
	struct linked_list *results,
	unsigned int clientsnb,
	options_t opts
)
{
	static struct netbench_test_info testinfolist[] =
		NETBENCH_TEST_INFO_LIST;
	static struct netbench_printer_info printerinfolist[] =
		NETBENCH_PRINTER_INFO_LIST;
	struct netbench_test_info *testptr;
	struct netbench_printer_info *prptr;

	testptr = testinfolist;

	while (testptr->type != NETBENCH_TEST_NONE)
	{
		if (OPT_GET(opts,testptr->optflag))
		{
			prptr = printerinfolist;
			while (prptr->type != NETBENCH_PRINTER_NONE)
			{
				if (OPT_GET(opts,prptr->optflag))
				{
					prptr->func(prptr->type,testptr->type,
						processes,results,clientsnb);
				}
				prptr++;
			}
		}
		testptr++;
	}
}
