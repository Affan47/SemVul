define_bool_tunable(int is_tunable)
{
	char *id, *bool_value;
	cond_bool_datum_t *datum;
	int ret;
	uint32_t value;

	if (pass == 2) {
		while ((id = queue_remove(id_queue)))
			free(id);
		return 0;
	}

	id = (char *)queue_remove(id_queue);
	if (!id) {
		yyerror("no identifier for bool definition?");
		return -1;
	}
	if (id_has_dot(id)) {
		free(id);
		yyerror("boolean identifiers may not contain periods");
		return -1;
	}
	datum = (cond_bool_datum_t *) malloc(sizeof(cond_bool_datum_t));
	if (!datum) {
		yyerror("out of memory");
		free(id);
		return -1;
	}
	memset(datum, 0, sizeof(cond_bool_datum_t));
	if (is_tunable)
		datum->flags |= COND_BOOL_FLAGS_TUNABLE;
	ret = declare_symbol(SYM_BOOLS, id, datum, &value, &value);
	switch (ret) {
	case -3:{
			yyerror("Out of memory!");
			goto cleanup;
		}
	case -2:{
			yyerror2("duplicate declaration of boolean %s", id);
			goto cleanup;
		}
	case -1:{
			yyerror("could not declare boolean here");
			goto cleanup;
		}
	case 0:
	case 1:{
			break;
		}
	default:{
			assert(0);
		}
	}
	datum->s.value = value;

	bool_value = (char *)queue_remove(id_queue);
	if (!bool_value) {
		yyerror("no default value for bool definition?");
		free(id);
		return -1;
	}

	datum->state = (int)(bool_value[0] == 'T') ? 1 : 0;
	return 0;
      cleanup:
	cond_destroy_bool(id, datum, NULL);
	return -1;
}
