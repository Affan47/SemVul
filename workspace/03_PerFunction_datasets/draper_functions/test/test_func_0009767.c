annotatemore_write_entry(const char *mboxname, const char *entry,
			     const char *userid,
			     const char *value, const char *contenttype,
			     size_t size, time_t modifiedsince,
			     struct txn **tid)
{
    struct annotation_data theentry;

    theentry.size = size;
    theentry.modifiedsince = modifiedsince ? modifiedsince : time(NULL);
    theentry.contenttype = contenttype ? contenttype : "text/plain";
    theentry.value = value ? value : "NIL";

    return write_entry(mboxname, entry, userid, &theentry, tid);
}
