scan_cmdline_to_pid_arg(struct text_object *obj, const char *arg, void* free_at_crash) {
	unsigned int i;

	if(strlen(arg) > 0) {
		obj->data.s = strdup(arg);
		for(i = 0; obj->data.s[i] != 0; i++) {
			while(obj->data.s[i] == ' ' && obj->data.s[i + 1] == ' ') {
				memmove(obj->data.s + i, obj->data.s + i + 1, strlen(obj->data.s + i + 1) + 1);
			}
		}
		if(obj->data.s[i - 1] == ' ') {
			obj->data.s[i - 1] = 0;
		}
	} else {
		CRIT_ERR(obj, free_at_crash, "${cmdline_to_pid commandline}");
	}
}
