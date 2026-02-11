filter_count_srv_status(const char *accept_field, const char *time_field, struct timer **tptr)
{
	const char *b, *e, *p;
	int f, err, array[5];
	struct ebmb_node *srv_node;
	struct srv_st *srv;
	int val;


	b = field_start(accept_field, SERVER_FIELD - ACCEPT_FIELD + 1);
	if (unlikely(!*b)) {
		truncated_line(linenum, line);
		return;
	}

	e = field_stop(b + 1);


	srv_node = ebst_lookup_len(&timers[0], b, e - b);
	srv = container_of(srv_node, struct srv_st, node);

	if (!srv_node) {

		srv = (void *)calloc(1, sizeof(struct srv_st) + e - b + 1);
		srv_node = &srv->node;
		memcpy(&srv_node->key, b, e - b);
		srv_node->key[e - b] = '\0';
		ebst_insert(&timers[0], srv_node);
	}


	if (!time_field) {
		time_field = field_start(e, TIME_FIELD - SERVER_FIELD);
		if (unlikely(!*time_field)) {
			truncated_line(linenum, line);
			return;
		}
	}

	e = field_stop(time_field + 1);


	p = time_field;
	err = 0;
	f = 0;
	while (!SEP(*p)) {
		array[f] = str2ic(p);
		if (array[f] < 0) {
			array[f] = -1;
			err = 1;
		}
		if (++f == 5)
			break;
		SKIP_CHAR(p, '/');
	}

	if (unlikely(f < 5)){
		parse_err++;
		return;
	}


	if (!err)
		srv->nb_ok++;

	if (array[2] >= 0) {
		srv->cum_ct += array[2];
		srv->nb_ct++;
	}

	if (array[3] >= 0) {
		srv->cum_rt += array[3];
		srv->nb_rt++;
	}


	b = field_start(e, STATUS_FIELD - TIME_FIELD);
	if (unlikely(!*b)) {
		truncated_line(linenum, line);
		return;
	}

	val = 0;
	if (*b >= '1' && *b <= '5')
		val = *b - '0';

	srv->st_cnt[val]++;
}
