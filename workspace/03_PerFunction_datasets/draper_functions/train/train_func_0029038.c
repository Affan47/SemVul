audit_mark_compare(struct audit_fsnotify_mark *mark, unsigned long ino, dev_t dev)
{
	if (mark->ino == AUDIT_INO_UNSET)
		return 0;
	return (mark->ino == ino) && (mark->dev == dev);
}
