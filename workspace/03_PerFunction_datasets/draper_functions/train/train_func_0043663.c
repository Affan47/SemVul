whlp_file_add(struct file *f, const void *data, int len)
{
    if (f->pos + len > f->size) {
	f->size = f->pos + len + 1024;
	f->data = sresize(f->data, f->size, unsigned char);
    }
    memcpy(f->data + f->pos, data, len);
    f->pos += len;
    if (f->len < f->pos)
	f->len = f->pos;
}
