number_compare_revisions(r1, r2)
struct RCSREV **r1, **r2 ;
{
    int r1maj, r1min, r2maj, r2min ;


    if (sscanf((*r1)->number, "r%d.%d", &r1maj, &r1min) != 2 ||
	sscanf((*r2)->number, "r%d.%d", &r2maj, &r2min) != 2) {
	fatal(REV_CORRUPT, MUSTNOT) ;
    }

    if (r1maj < r2maj) {
	return -1 ;
    } else if (r1maj > r2maj) {
	return 1 ;
    } else {
	if (r1min < r2min) {
	    return -1 ;
	} else if (r1min > r2min) {
	    return 1 ;
	} else {
	    return 0 ;
	}
    }
}
