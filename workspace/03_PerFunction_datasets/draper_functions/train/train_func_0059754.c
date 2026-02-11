dots_finish_percents(struct file_info *info, int process_res)
{
	char buf[80];
	info->error = process_res;

	if((percents.points % 74) != 0) {
		log_msg("%s 100%%\n", str_set(buf, ' ', 74 - (percents.points%74) ));
	}
	print_results_on_check(info, 0);
}
