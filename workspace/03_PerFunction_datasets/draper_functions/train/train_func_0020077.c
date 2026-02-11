kalman_retrieve_matrix (const char *name,
					     int level, int cfd)
{
    gretl_matrix *m;

    if (*name == '\0') {
	return NULL;
    }


    m = get_matrix_by_name_at_level(name, level);
    if (m == NULL && level < cfd) {
	m = get_matrix_by_name_at_level(name, cfd);
    }

    return m;
}
