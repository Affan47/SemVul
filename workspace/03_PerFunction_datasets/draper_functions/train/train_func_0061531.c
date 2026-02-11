gravitate(int multiplier)
{
    	int dy = 0;
    	int gravity = (size->flags & PWinGravity) ?
        	size->win_gravity : NorthWestGravity;

    	switch (gravity) {
        	case NorthWestGravity:
        	case NorthEastGravity:
        	case NorthGravity: dy = theight(); break;
        	case CenterGravity: dy = theight()/2; break;
    	}

   	y += multiplier * dy;
}
