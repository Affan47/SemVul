InsChrInsert(void) {
    long ch = InsChrUniVal();
    GEvent e;

    e.type = et_char;
    e.w = GWidgetGetPreviousFocusTopWindow();
    if ( e.w==NULL || e.w==inschr.icw ) {
	GDrawBeep(NULL);
return;
    }
    e.u.chr.state = 0;
    e.u.chr.x = e.u.chr.y = -1;
    e.u.chr.keysym = 0;
    e.u.chr.chars[0] = ch;
    e.u.chr.chars[1] = '\0';
    GDrawPostEvent(&e);
}
