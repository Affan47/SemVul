patch_set_member_regex(PatchSet * ps, regex_t * reg)
{
    struct list_head * next = ps->members.next;

    while (next != &ps->members)
    {
	PatchSetMember * psm = list_entry(next, PatchSetMember, link);

	if (regexec(&restrict_file, psm->file->filename, 0, NULL, 0) == 0)
	    return 1;

	next = next->next;
    }

    return 0;
}
