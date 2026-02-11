readCtrlChar() {
    static String controls = "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_";
    String which;

    skip();
    if ((which = strchr(controls,c0))==NULL) {
	ERRMSG(row) "Unrecognised escape sequence `\\^%c'", c0
	EEND;
    }
    skip();
    return mkChar(which-controls);
}
