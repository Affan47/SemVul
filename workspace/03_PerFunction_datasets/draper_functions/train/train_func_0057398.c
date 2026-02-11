lastdelim2x (boolean more, boolean lastrow)
{
    if (more) {
	lput(" ");
    } else {
	if(lastrow) {
	    lput("\n   ");
	} else {
	    lput("\n     ");
	}
    }
}
