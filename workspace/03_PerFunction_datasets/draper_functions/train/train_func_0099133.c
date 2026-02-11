status_tostr(char *str, struct scdata *sc)
{
	int i;
	char *str_p = str;

	nullpo_retr(1, sc);

	str_p += sprintf(str,"%d,%d\t",sc->char_id, sc->account_id);

	for(i = 0; i < sc->count; i++) {
		str_p += sprintf(str_p, "%d,%d,%d,%d,%d,%d ",
			sc->data[i].type, sc->data[i].val1, sc->data[i].val2, sc->data[i].val3, sc->data[i].val4, sc->data[i].tick);
	}
	*(str_p++) = '\t';

	*str_p = '\0';
	return 0;
}
