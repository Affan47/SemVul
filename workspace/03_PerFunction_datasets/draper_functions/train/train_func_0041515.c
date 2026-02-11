at2_read_line(PrivAT2data *privdata, int gt_flag)
{
    int	eol;
    int gtloc;
    int len;
    Octstr *line;
    Octstr *buf2;
    int i;

    at2_read_buffer(privdata);
    at2_scan_for_telnet_escapes(privdata);
    len = octstr_len(privdata->ilb);
    if (len == 0)
        return NULL;

    if (gt_flag==1) {

        gtloc = octstr_search_char(privdata->ilb, '>', 0);
    }
    else if((gt_flag == 2) && (privdata->username)) {
        gtloc = -1;
        if(privdata->login_prompt) {
            gtloc = octstr_search(privdata->ilb,privdata->login_prompt,0);
        }
        if(gtloc == -1) {
            gtloc = octstr_search(privdata->ilb,octstr_imm("Login:"),0);
        }
        if(gtloc == -1) {
            gtloc = octstr_search(privdata->ilb,octstr_imm("Username:"),0);
        }
    }
    else if ((gt_flag == 3) && (privdata->password)) {
    	gtloc = -1;
        if(privdata->password_prompt) {
            gtloc = octstr_search(privdata->ilb,privdata->password_prompt,0);
        }
        if(gtloc == -1) {
            gtloc = octstr_search(privdata->ilb,octstr_imm("Password:"),0);
        }
    }
    else
        gtloc = -1;


    eol = octstr_search_char(privdata->ilb, '\r', 0);

    if ((gtloc != -1) && ((eol == -1) || (eol > gtloc)))
        eol = gtloc;

    if (eol == -1)
        return NULL;

    line = octstr_copy(privdata->ilb, 0, eol);
    buf2 = octstr_copy(privdata->ilb, eol + 1, len);
    octstr_destroy(privdata->ilb);
    privdata->ilb = buf2;


    for (i = 0; i < octstr_len(line); i++) {
        if (octstr_get_char(line, i) < 32)
            octstr_set_char(line, i, ' ');
    }
    octstr_strip_blanks(line);


    if ((strcmp(octstr_get_cstr(line), "") == 0) && ( gt_flag == 0))
    {
        octstr_destroy(line);
        return NULL;
    }
    if ((gt_flag) && (gtloc != -1)) {

        octstr_append_cstr(line, ">");
    }
    debug("bb.smsc.at2", 0, "AT2[%s]: <-- %s", octstr_get_cstr(privdata->name),
          octstr_get_cstr(line));
    return line;
}
