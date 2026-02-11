taitoic_drawscanline(
		struct mame_bitmap *bitmap,int x,int y,
		const UINT16 *src,int transparent,UINT32 orient,int pri, const struct rectangle *cliprect)
{
	ADJUST_FOR_ORIENTATION(UINT16, Machine->orientation ^ orient, bitmap, priority_bitmap, x, y);
	{
		int length=cliprect->max_x - cliprect->min_x + 1;
		src+=cliprect->min_x;
		dsti+=xadv * cliprect->min_x;
		dstp+=xadv * cliprect->min_x;
		if (transparent) {
			while (length--) {
				UINT32 spixel = *src++;
				if (spixel<0x7fff) {
					*dsti = spixel;
					*dstp = pri;
				}
				dsti += xadv;
				dstp += xadv;
			}
		} else {
			while (length--) {
				*dsti = *src++;
				*dstp = pri;
				dsti += xadv;
				dstp += xadv;
			}
		}
	}
}
