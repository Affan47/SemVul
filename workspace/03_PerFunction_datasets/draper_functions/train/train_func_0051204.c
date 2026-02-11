CORD_cmp(CORD x, CORD y)
{
    CORD_pos xpos;
    CORD_pos ypos;
    register size_t avail, yavail;

    if (y == CORD_EMPTY) return(x != CORD_EMPTY);
    if (x == CORD_EMPTY) return(-1);
	if (x == y) return (0);
    if (CORD_IS_STRING(y) && CORD_IS_STRING(x)) return(strcmp(x,y));
    CORD_set_pos(xpos, x, 0);
    CORD_set_pos(ypos, y, 0);
    for(;;) {
        if (!CORD_pos_valid(xpos)) {
            if (CORD_pos_valid(ypos)) {
            	return(-1);
            } else {
                return(0);
            }
        }
        if (!CORD_pos_valid(ypos)) {
            return(1);
        }
        if ((avail = CORD_pos_chars_left(xpos)) <= 0
            || (yavail = CORD_pos_chars_left(ypos)) <= 0) {
            register char xcurrent = CORD_pos_fetch(xpos);
            register char ycurrent = CORD_pos_fetch(ypos);
            if (xcurrent != ycurrent) return(xcurrent - ycurrent);
            CORD_next(xpos);
            CORD_next(ypos);
        } else {

            register int result;

            if (avail > yavail) avail = yavail;
            result = strncmp(CORD_pos_cur_char_addr(xpos),
            		     CORD_pos_cur_char_addr(ypos), avail);
            if (result != 0) return(result);
            CORD_pos_advance(xpos, avail);
            CORD_pos_advance(ypos, avail);
        }
    }
}
