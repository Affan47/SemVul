remove_ring(void)
{
    boolean left = 0, right = 0;
    short ch;
    char buf[ROGUE_COLUMNS];
    object *ring;

    if (r_rings == 0) {
	inv_rings();
    } else if (rogue.left_ring && !rogue.right_ring) {
	left = 1;
    } else if (!rogue.left_ring && rogue.right_ring) {
	right = 1;
    } else {
	message(left_or_right, 0);
	do {
	    ch = rgetchar();
#if defined( JAPAN )
	    if (ch == 'L') {
		ch = 'l';
	    }
	    if (ch == 'R') {
		ch = 'r';
	    }
#endif
	} while ((ch != CANCEL) && (ch != 'l') && (ch != 'r') &&
		 (ch != '\n') && (ch != '\r'));
	left = (ch == 'l');
	right = (ch == 'r');
	check_message();
    }
    if (left || right) {
	if (left && rogue.left_ring) {
	    ring = rogue.left_ring;
	} else if (right && rogue.right_ring) {
	    ring = rogue.right_ring;
	} else {
	    message(no_ring, 0);
	    ring = rogue.right_ring;
	}
	if (ring->is_cursed) {
	    message(curse_message, 0);
	} else {
	    un_put_on(ring);
#if defined( JAPAN )
	    get_desc(ring, buf, 0);
	    (void) strcat(buf, mesg[166]);
#else
	    (void) strcpy(buf, mesg[166]);
	    get_desc(ring, buf + strlen(mesg[166]), 0);
#endif
	    message(buf, 0);
	    (void) reg_move();
	}
    }
}
