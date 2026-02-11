outline_descr(dico_handle_t hp)
{
    struct outline_file *file = (struct outline_file *) hp;
    if (file->descr_entry) {
	char *buf = read_buf(file, file->descr_entry);
	char *p = strchr(buf, '\n');
	if (p)
	    *p = 0;
	return buf;
    }
    return NULL;
}
