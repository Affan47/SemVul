_server_writable(eio_obj_t *obj)
{
	struct server_io_info *s = (struct server_io_info *) obj->arg;

	debug4("Called _server_writable");

	if (s->out_eof) {
		debug4("  false, eof");
		return false;
	}
	if (obj->shutdown == true) {
		debug4("  false, shutdown");
		return false;
	}
	if (s->out_msg != NULL
	    || !list_is_empty(s->msg_queue)) {
		debug4("  true, s->msg_queue length = %d",
		       list_count(s->msg_queue));
		return true;
	}

	debug4("  false");
	return false;
}
