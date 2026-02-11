set_hidden3doptions()
{
    int tmp;

    while (!END_OF_COMMAND) {
	switch (lookup_table(&set_hidden3d_tbl[0], c_token)) {
	case S_HI_DEFAULTS:

	    reset_hidden3doptions();
	    c_token++;
	    if (!END_OF_COMMAND)
		int_error(c_token,
			  "No further options allowed after 'defaults'");
	    return;
	    break;
	case S_HI_OFFSET:
	    c_token++;
	    hiddenBacksideLinetypeOffset = int_expression();
	    c_token--;
	    break;
	case S_HI_NOOFFSET:
	    hiddenBacksideLinetypeOffset = 0;
	    break;
	case S_HI_TRIANGLEPATTERN:
	    c_token++;
	    hiddenTriangleLinesdrawnPattern = int_expression();
	    c_token--;
	    break;
	case S_HI_UNDEFINED:
	    c_token++;
	    tmp = int_expression();
	    if (tmp <= 0 || tmp > UNHANDLED)
		tmp = UNHANDLED;
	    hiddenHandleUndefinedPoints = tmp;
	    c_token--;
	    break;
	case S_HI_NOUNDEFINED:
	    hiddenHandleUndefinedPoints = UNHANDLED;
	    break;
	case S_HI_ALTDIAGONAL:
	    hiddenShowAlternativeDiagonal = 1;
	    break;
	case S_HI_NOALTDIAGONAL:
	    hiddenShowAlternativeDiagonal = 0;
	    break;
	case S_HI_BENTOVER:
	    hiddenHandleBentoverQuadrangles = 1;
	    break;
	case S_HI_NOBENTOVER:
	    hiddenHandleBentoverQuadrangles = 0;
	    break;
	case S_HI_BACK:
	    hidden3d_layer = LAYER_BACK;
	    break;
	case S_HI_FRONT:
	    hidden3d_layer = LAYER_FRONT;
	    break;
	case S_HI_INVALID:
	    int_error(c_token, "No such option to hidden3d (or wrong order)");
	default:
	    break;
	}
	c_token++;
    }
}
