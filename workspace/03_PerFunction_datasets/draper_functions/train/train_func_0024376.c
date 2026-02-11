look_up_warnmsg (int w)
{
    if (w > 0 && w < W_MAX) {
	return gretl_warning_messages[w];
    } else {
	fprintf(stderr, "look_up_warnmsg: out of bounds code %d\n", w);
	return "missing warning message!";
    }
}
