CORD_lf_close_proc(void * obj, void * client_data)
{
    if (fclose(((lf_state *)obj) -> lf_file) != 0) {
    	ABORT("CORD_lf_close_proc: fclose failed");
    }
}
