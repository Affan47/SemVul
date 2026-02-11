show_commit(struct commit *commit)
{
	if (commit->object.flags & BOUNDARY)
		fputc('-', pack_pipe);
	if (fputs(sha1_to_hex(commit->object.sha1), pack_pipe) < 0)
		die("broken output pipe");
	fputc('\n', pack_pipe);
	fflush(pack_pipe);
	free(commit->buffer);
	commit->buffer = NULL;
}
