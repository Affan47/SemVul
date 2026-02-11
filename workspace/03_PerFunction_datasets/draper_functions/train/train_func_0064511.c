print_summary(void)
{
	printf("\n## Summary: %d nodes checked, %d bad nodes found\n",
		summary.nodes_checked, summary.bad_nodes);
	printf("##          %d ports checked, %d ports have errors beyond threshold\n",
		summary.ports_checked, summary.bad_ports);
	printf("## %s\n", threshold_str);
	if (summary.pma_query_failures)
		printf("##          %d PMA query failures\n", summary.pma_query_failures);
	report_suppressed();
	return (summary.bad_ports);
}
