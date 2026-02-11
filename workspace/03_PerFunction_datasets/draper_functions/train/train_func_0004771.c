packlist_get(git_odb *db)
{
	git_packlist *pl;

	gitlck_lock(&db->lock);
	if ((pl = db->packlist) != NULL)
		pl->refcnt++;
	else
		pl = scan_packs(db);
	gitlck_unlock(&db->lock);
	return pl;
}
