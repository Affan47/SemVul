equalsGenericCell(generic_cell c1, generic_cell c2)
{
    if ((c1.t) != (c2.t)) {
	return GC_DIFFERENT_TYPE;
    }
    switch (c1.t) {
    case CELL_TYPE:
	{
	    if (((c1.val).c) > ((c2.val).c))
		return GC_HIGHER;
	    else {
		if (((c1.val).c) == ((c2.val).c))
		    return GC_EQUAL;
		else
		    return GC_LOWER;
	    }
	    break;
	}
    case DCELL_TYPE:
	{
	    if (((c1.val).dc) > ((c2.val).dc))
		return GC_HIGHER;
	    else {
		if (((c1.val).dc) == ((c2.val).dc))
		    return GC_EQUAL;
		else
		    return GC_LOWER;
	    }
	    break;
	}
    case FCELL_TYPE:
	{
	    if (((c1.val).fc) > ((c2.val).fc))
		return GC_HIGHER;
	    else {
		if (((c1.val).fc) == ((c2.val).fc))
		    return GC_EQUAL;
		else
		    return GC_LOWER;
	    }
	    break;
	}
    default:
	{
	    return GC_ERR_UNKNOWN;
	    break;
	}
    }
}
