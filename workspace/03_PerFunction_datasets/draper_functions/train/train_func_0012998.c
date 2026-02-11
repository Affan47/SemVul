trace_on_exit(int status,void *dummy)
{
    char path[PATH_MAX+1];
    FILE *file;

    if (!status) return;
    if (!dump_dir) file = stderr;
    else {
	sprintf(path,"atmsigd.%d.trace.exit",getpid());
	if (!(file = fopen(path,"w"))) {
	    perror(path);
	    file = stderr;
	}
    }
    dump_trace(file,"Message trace (after error exit)");
    if (file != stderr) (void) fclose(file);
}
