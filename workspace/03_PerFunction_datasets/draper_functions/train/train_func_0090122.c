apol_relabel_analysis_append_subject(const apol_policy_t * p, apol_relabel_analysis_t * r, const char *subject)
{
	char *s;
	if (p == NULL || r == NULL) {
		ERR(p, "%s", strerror(EINVAL));
		return -1;
	}
	if (subject == NULL) {
		apol_vector_destroy(&r->subjects);
	} else if ((s = strdup(subject)) == NULL ||
		   (r->subjects == NULL && (r->subjects = apol_vector_create(free)) == NULL) ||
		   apol_vector_append(r->subjects, s) < 0) {
		ERR(p, "%s", strerror(errno));
		return -1;
	}
	return 0;
}
