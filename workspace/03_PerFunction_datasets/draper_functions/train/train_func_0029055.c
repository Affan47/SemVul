progress_update(struct progress_struct *progress, __u32 val)
{
	if ((progress->format[0] == 0) || progress->skip_progress)
		return;
	printf(progress->format, val, progress->max);
	fputs(progress->backup, stdout);
}
