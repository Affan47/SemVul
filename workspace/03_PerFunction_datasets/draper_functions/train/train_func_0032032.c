pcap_freecode(struct bpf_program *program)
{
	program->bf_len = 0;
	if (program->bf_insns != NULL) {
		free((char *)program->bf_insns);
		program->bf_insns = NULL;
	}
}
