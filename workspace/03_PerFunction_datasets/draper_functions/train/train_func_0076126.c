matchesDirPathLists(struct sStringList *includes,
				struct sStringList *includes_recursion,
				struct sStringList *excludes,
				struct sStringList *excludes_recursion,
				char str[MAX_PATH_LEN+1]) {


	int32_t incl, incl_rec, excl, excl_rec;

	incl=matchesStringList(includes, str);
	incl_rec=matchesStringList(includes_recursion, str);
	excl=matchesStringList(excludes, str);
	excl_rec=matchesStringList(excludes_recursion, str);


	if ((includes->next==NULL) && (includes_recursion->next==NULL)) {


		if ((excl != RETURN_EXACT_MATCH) && (excl_rec == RETURN_NO_MATCH)) {
			return 1;
		}

	} else {


		if (((incl == RETURN_EXACT_MATCH) || (incl_rec != RETURN_NO_MATCH)) &&
		      (excl != RETURN_EXACT_MATCH) && (excl_rec == RETURN_NO_MATCH)) {
			return 1;
		}
	}

	return 0;
}
