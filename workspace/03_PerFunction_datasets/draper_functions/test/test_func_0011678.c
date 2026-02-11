peek(json_pull *j) {
	if (j->buffer_head < j->buffer_tail) {
		return j->buffer[j->buffer_head];
	} else {
		j->buffer_head = 0;
		j->buffer_tail = j->read(j, j->buffer, BUFFER);
		if (j->buffer_head >= j->buffer_tail) {
			return EOF;
		}
		return j->buffer[j->buffer_head];
	}
}
