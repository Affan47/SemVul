rev_commit_locate_date (rev_ref *branch, time_t date)
{
    rev_commit	*commit;

    for (commit = branch->commit; commit; commit = commit->parent)
    {
	if (time_compare (commit->date, date) <= 0)
	    return commit;
    }
    return NULL;
}
