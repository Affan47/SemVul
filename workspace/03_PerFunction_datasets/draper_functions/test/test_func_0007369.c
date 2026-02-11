cmdline_get_passwd_input(prompts_t *p, unsigned char *in, int inlen) {

    static int tried_once = 0;


    if (!cmdline_password || in || p->n_prompts != 1 || p->prompts[0]->echo) {
	return -1;
    }


    if (tried_once)
	return 0;

    strncpy(p->prompts[0]->result, cmdline_password,
	    p->prompts[0]->result_len);
    p->prompts[0]->result[p->prompts[0]->result_len-1] = '\0';
    memset(cmdline_password, 0, strlen(cmdline_password));
    sfree(cmdline_password);
    cmdline_password = NULL;
    tried_once = 1;
    return 1;

}
