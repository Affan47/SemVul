end_code(void)
{
    int indent,i;

    indent = 1;
    for (i = 0; i < pc; i++) {
	if (indent) {
	    to_c("    ");
	    indent = 0;
	}
	to_c(buf[i].data);
	if (buf[i].extra && *buf[i].extra == '\n') to_c(",");
	else to_c(", ");
	if (buf[i].extra) {
	    to_c(buf[i].extra);
	    indent = !!strchr(buf[i].extra,'\n');
	    if (indent) to_c("/*%4d*/",i+1);
	}
    }
    return pc;
}
