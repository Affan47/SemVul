node_enum(EditLine *el, key_node_t *ptr, size_t cnt)
{
        ssize_t used;

	if (cnt >= KEY_BUFSIZ - 5) {
		el->el_key.buf[++cnt] = '"';
		el->el_key.buf[++cnt] = '\0';
		(void) fprintf(el->el_errfile,
		    "Some extended keys too long for internal print buffer");
		(void) fprintf(el->el_errfile, " \"" FSTR "...\"\n", el->el_key.buf);
		return (0);
	}
	if (ptr == NULL) {
#ifdef DEBUG_EDIT
		(void) fprintf(el->el_errfile,
		    "node_enum: BUG!! Null ptr passed\n!");
#endif
		return (-1);
	}

        used = ct_visual_char(el->el_key.buf + cnt, KEY_BUFSIZ - cnt, ptr->ch);
	if (ptr->next == NULL) {

		el->el_key.buf[cnt + used   ] = '"';
		el->el_key.buf[cnt + used + 1] = '\0';
		key_kprint(el, el->el_key.buf, &ptr->val, ptr->type);
	} else
		(void) node_enum(el, ptr->next, cnt + used);


	if (ptr->sibling)
		(void) node_enum(el, ptr->sibling, cnt);
	return (0);
}
