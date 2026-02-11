build_suffixtree_ascend(struct node *n, struct text_buffer *buf, struct node *prev, suffix_callback cb, void *cbdata, struct regex_list *regex)
{
	size_t i, cnt;
	while(n) {
		struct node *q = n;
		switch(n->type) {
			case root:
				textbuffer_putc(buf, '\0');
				if(cb(cbdata, buf->data, buf->pos-1, regex) < 0)
					return CL_EMEM;
				return 0;
			case leaf:
				textbuffer_putc(buf, n->u.leaf_char);
				n = n->parent;
				break;
			case leaf_class:
				cnt = 0;
				for(i=0;i<255;i++)
					if (BITMAP_HASSET(n->u.leaf_class_bitmap, i))
						cnt++;
				if (cnt > 16) {
					textbuffer_putc(buf, '\0');
					if(cb(cbdata, buf->data, buf->pos-1, regex) < 0)
						return CL_EMEM;
					return 0;
				}

				for(i=0;i<255;i++) {
					if(BITMAP_HASSET(n->u.leaf_class_bitmap, i)) {
						size_t pos;
						pos = buf->pos;
						textbuffer_putc(buf, i);
						if(build_suffixtree_ascend(n->parent, buf, n, cb, cbdata, regex) < 0)
							return CL_EMEM;
						buf->pos = pos;
					}
				}
				return 0;
			case concat:
				if(prev != n->u.children.left) {
					if(build_suffixtree_descend(n->u.children.left, buf, cb, cbdata, regex) < 0)
						return CL_EMEM;


					return 0;
				} else {
					n = n->parent;
				}
				break;
			case alternate:
				n = n->parent;
				break;
			case optional:
				textbuffer_putc(buf, '\0');
				if(cb(cbdata, buf->data, buf->pos-1, regex) < 0)
					return CL_EMEM;
				return 0;
		}
		prev = q;
	}
	return 0;
}
