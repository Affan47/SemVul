add_file_history_entry(char *n)
{
	List *hist=(List*)getAtomValue(HISTATOM_FILE);
	if (hist) insert_history_entry(hist, n, 0);
}
