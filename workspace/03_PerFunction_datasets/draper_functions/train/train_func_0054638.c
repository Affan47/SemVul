GGadgetProtest8(char *label) {
    char buf[80];

    snprintf( buf, sizeof(buf),_("Bad Number in %s"), label);
    if ( buf[strlen(buf)-1]==' ' )
	buf[strlen(buf)-1]='\0';
    if ( buf[strlen(buf)-1]==':' )
	buf[strlen(buf)-1]='\0';
    gwwv_post_notice(buf,buf);
}
