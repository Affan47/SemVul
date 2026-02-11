rb_linebuf_attach(buf_head_t * bufhead, buf_head_t * new)
{
	rb_dlink_node *ptr;
	buf_line_t *line;

	RB_DLINK_FOREACH(ptr, new->list.head)
	{
		line = ptr->data;
		rb_dlinkAddTailAlloc(line, &bufhead->list);


		bufhead->alloclen++;
		bufhead->len += line->len;
		bufhead->numlines++;

		line->refcount++;
	}
}
