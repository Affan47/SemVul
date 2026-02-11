count_categories(olist, qflags)
struct obj *olist;
int qflags;
{
	char *pack;
	boolean counted_category;
	int ccount = 0;
	struct obj *curr;

	pack = flags.inv_order;
	do {
	    counted_category = FALSE;
	    for (curr = olist; curr; curr = FOLLOW(curr, qflags)) {
		if (curr->oclass == *pack) {
		   if ((qflags & WORN_TYPES) &&
		    	!(curr->owornmask & (W_ARMOR | W_RING | W_AMUL | W_TOOL |
		    	W_WEP | W_SWAPWEP | W_QUIVER)))
			 continue;
		   if (!counted_category) {
			ccount++;
			counted_category = TRUE;
		   }
		}
	    }
	    pack++;
	} while (*pack);
	return ccount;
}
