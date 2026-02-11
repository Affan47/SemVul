error_report(const char *module_name, const char *filename, LINENO_t lineno,
	     const char *topfile, LINENO_t top_lineno,
	     int i, const char *item_tag, const char *item_name, const char *msg)
#else
error_report(module_name, filename, lineno,
	     topfile, top_lineno,
	     i, item_tag, item_name, msg)
    char *module_name;
    char *filename;
    LINENO_t lineno;
    char *topfile;
    LINENO_t top_lineno;
    int i;
    char *item_tag;
    char *item_name;
    char *msg;
#endif
{
    if( ! at_position_printed ) {
	char posn[12+3*sizeof(int)+2];
	(void)sprintf(posn,"at position %d:",i+1);
	msg_tail(posn);
	at_position_printed = TRUE;
    }

    report_intro(filename,lineno,topfile,top_lineno);
    msg_tail(item_tag);

    msg_tail(item_name);


    module_locate(module_name);

    if( novice_help ) {

	novice_err_locate(filename,lineno);

	novice_inc_locate(filename,topfile,top_lineno);
    }

    msg_tail(msg);

}
