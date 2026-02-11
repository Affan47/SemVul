git_odb_close(git_odb *db)
{
	git_packlist *pl;

	if (!db)
		return;

	gitlck_lock(&db->lock);

	pl = db->packlist;
	db->packlist = NULL;

	if (db->alternates) {
		git_odb **alt;
		for (alt = db->alternates; *alt; alt++)
			git_odb_close(*alt);
		free(db->alternates);
	}

	free(db->objects_dir);

	gitlck_unlock(&db->lock);
	if (pl)
		packlist_dec(db, pl);
	gitlck_free(&db->lock);
	free(db);
}
