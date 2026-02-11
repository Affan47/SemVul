hook_destroy_cb(void *framedata)
{
	ast_debug(1, "JITTERBUFFER hook destroyed\n");
	jb_framedata_destroy((struct jb_framedata *) framedata);
}
