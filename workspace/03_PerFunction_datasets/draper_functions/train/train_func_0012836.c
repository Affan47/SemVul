tdb_dump_record(struct tdb_context *tdb, int hash,
				 tdb_off_t offset)
{
	struct list_struct rec;
	tdb_off_t tailer_ofs, tailer;

	if (tdb->methods->tdb_read(tdb, offset, (char *)&rec,
				   sizeof(rec), DOCONV()) == -1) {
		printf("ERROR: failed to read record at %u\n", offset);
		return 0;
	}

	printf(" rec: hash=%d offset=0x%08x next=0x%08x rec_len=%d "
	       "key_len=%d data_len=%d full_hash=0x%x magic=0x%x\n",
	       hash, offset, rec.next, rec.rec_len, rec.key_len, rec.data_len,
	       rec.full_hash, rec.magic);

	tailer_ofs = offset + sizeof(rec) + rec.rec_len - sizeof(tdb_off_t);

	if (tdb_ofs_read(tdb, tailer_ofs, &tailer) == -1) {
		printf("ERROR: failed to read tailer at %u\n", tailer_ofs);
		return rec.next;
	}

	if (tailer != rec.rec_len + sizeof(rec)) {
		printf("ERROR: tailer does not match record! tailer=%u totalsize=%u\n",
				(unsigned int)tailer, (unsigned int)(rec.rec_len + sizeof(rec)));
	}
	return rec.next;
}
