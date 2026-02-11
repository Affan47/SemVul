parse_as_for_loop (LOOPSET *loop, char *s)
{
    char *tmp, *q;
    int i, j, len;
    int sc = 0;
    int err = 0;

    s += strcspn(s, "(");
    if (*s != '(') {
	return E_PARSE;
    }

    s++;
    q = strrchr(s, ')');
    if (q == NULL) {
	return E_PARSE;
    }

    len = q - s;
    if (len < 2) {
	return E_PARSE;
    }

    tmp = malloc(len + 1);
    if (tmp == NULL) {
	return E_ALLOC;
    }

    for (j=0; j<3 && s!=q && !err; j++) {

	i = 0;
	while (s != q) {
	    if (*s == ';') {
		sc++;
		s++;
		break;
	    }
	    if (*s != ' ') {
		tmp[i++] = *s;
	    }
	    s++;
	}
	tmp[i] = '\0';
	err = set_forloop_element(tmp, loop, j);
    }

    if (!err && (sc != 2 || s != q)) {


	err = E_PARSE;
    }

    free(tmp);

    if (!err) {
	loop->type = FOR_LOOP;
    }

    return err;
}
