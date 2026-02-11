fs_read(loff_t pos, int size, void *data)
{
    CHANGE *walk;
    int got;

    if (llseek(fd, pos, 0) != pos)
	pdie("Seek to %lld", pos);
    if ((got = read(fd, data, size)) < 0)
	pdie("Read %d bytes at %lld", size, pos);
    if (got != size)
	die("Got %d bytes instead of %d at %lld", got, size, pos);
    for (walk = changes; walk; walk = walk->next) {
	if (walk->pos < pos + size && walk->pos + walk->size > pos) {
	    if (walk->pos < pos)
		memcpy(data, (char *)walk->data + pos - walk->pos, min(size,
								       walk->size
								       - pos +
								       walk->pos));
	    else
		memcpy((char *)data + walk->pos - pos, walk->data,
		       min(walk->size, size + pos - walk->pos));
	}
    }
}
