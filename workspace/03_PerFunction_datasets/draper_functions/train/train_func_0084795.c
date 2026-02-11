ArchStatMember(const char *archive, const char *member, Boolean hash)
{
	struct arfile	*arf;
	int64_t		ret;
	int		t;
	char		*cp;
	Arch		*ar;
	Hash_Entry	*he;
	char		copy[AR_NAMSIZ + 1];


	if (member != NULL) {
		cp = strrchr(member, '/');
		if (cp != NULL)
			member = cp + 1;
	}

	TAILQ_FOREACH(ar, &archives, link) {
		if (strcmp(archive, ar->name) == 0)
			break;
	}
	if (ar == NULL) {

		if (!hash) {


			arf = ArchFindMember(archive, member, "r");
			if (arf == NULL) {
				return (INT64_MIN);
			}
			ret = arf->time;
			ArchArchiveClose(arf);
			return (ret);
		}


		arf = ArchArchiveOpen(archive, "r");
		if (arf == NULL) {
			return (INT64_MIN);
		}


		ar = emalloc(sizeof(*ar));
		ar->name = estrdup(archive);
		Hash_InitTable(&ar->members, -1);

		while ((t = ArchArchiveNext(arf)) > 0) {
			he = Hash_CreateEntry(&ar->members, arf->member, NULL);
			Hash_SetValue(he, emalloc(sizeof(int64_t)));
			*(int64_t *)Hash_GetValue(he) = arf->time;
		}

		ArchArchiveClose(arf);

		if (t < 0) {

			Hash_DeleteTable(&ar->members);
			free(ar->name);
			free(ar);
			return (INT64_MIN);
		}

		TAILQ_INSERT_TAIL(&archives, ar, link);
	}


	he = Hash_FindEntry(&ar->members, member);
	if (he != NULL)
		return (*(int64_t *)Hash_GetValue (he));

	if (member != NULL && strlen(member) > AR_NAMSIZ) {

		strlcpy(copy, member, AR_NAMSIZ + 1);

		if ((he = Hash_FindEntry(&ar->members, copy)) != NULL)
			return (*(int64_t *)Hash_GetValue(he));
	}

	return (INT64_MIN);
}
