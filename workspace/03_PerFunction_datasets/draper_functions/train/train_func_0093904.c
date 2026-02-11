findCloserSticker (double distance, double location [],
				 int faceCentre [])
{
    double    len          = 0.0;
    double    dmin         = distance;
    Sticker * foundSticker = 0;

    foreach (Sticker * sticker, stickers) {
	double d = 0.0;
	LOOP (n, nAxes) {
	    len = location[n] - sticker->currentFaceCentre[n];
	    d   = d + len * len;
	}
	d = sqrt (d);
	if (d < dmin) {
	    dmin = d;
	    foundSticker = sticker;
	}
    }

    if (foundSticker != 0) {
	LOOP (n, nAxes) {
	    faceCentre[n] = foundSticker->currentFaceCentre[n];
	}
    }

    return (dmin);
}
