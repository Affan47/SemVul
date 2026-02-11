tdb_increment_seqnum_nonblock(struct tdb_context *tdb)
{
	tdb_off_t seqnum=0;

	if (!(tdb->flags & TDB_SEQNUM)) {
		return;
	}


	tdb_ofs_read(tdb, TDB_SEQNUM_OFS, &seqnum);
	seqnum++;
	tdb_ofs_write(tdb, TDB_SEQNUM_OFS, &seqnum);
}
