cram_flush_thread(void *arg) {
    cram_job *j = (cram_job *)arg;


    if (0 != cram_encode_container(j->fd, j->c)) {
	fprintf(stderr, "cram_encode_container failed\n");
	return NULL;
    }

    return arg;
}
