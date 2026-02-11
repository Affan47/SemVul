s3_combine(struct srec_data *srec)
{
	int from, to, removed;

	from = to = removed = 0;
	while (from < srec->s3_used) {
		struct s3_record *_to, *_to_1, *_from;
		_to = &srec->s3_records[to];
		_to_1 = to > 0 ? &srec->s3_records[to - 1] : NULL;
		_from = &srec->s3_records[from];

		if (_from->len == 0) {
			removed++;
			from++;
			continue;
		}

		if (to != 0 && _to_1->addr + _to_1->len == _from->addr) {
			_to_1->data = (unsigned char *)
				realloc(_to_1->data, _to_1->len + _from->len);
			if (_to_1->data == NULL) {
				printf("realloc() failed\n");
				return 1;
			}
			memcpy(_to_1->data + _to_1->len, _from->data,
			       _from->len);
			free(_from->data);
			_from->data = NULL;
			_to_1->len += _from->len;
			removed++;
		} else {
			if (from != to)
				memcpy(_to, _from, sizeof(struct s3_record));
			to++;
		}
		from++;
	}

	srec->s3_used -= removed;

	if (srec->s3_entries > srec->s3_used) {
		srec->s3_entries = srec->s3_used;
		srec->s3_records = (struct s3_record *)
			realloc(srec->s3_records,
				srec->s3_entries * sizeof(struct s3_record));
		if (srec->s3_records == NULL) {
			printf("realloc() failed\n");
			return 1;
		}
	}

	return 0;
}
