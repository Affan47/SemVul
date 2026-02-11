makeHisto()
{
    int i, spp, val;
    long nbpix;
    unsigned char *p, *end;

    for (i = 0 ; i < 256 ; i++)
	theHisto[i] = 0;

    nbpix = (long)IOBlackBox->imageWidth() * (long)IOBlackBox->imageHeight();
    spp = IOBlackBox->imageDepth();

    if (spp == 1) {
	p = IOBlackBox->imageData();
	end = p + nbpix;

	while (p != end) {
	    theHisto[*p++]++;
	}
    } else if (spp == 3) {

	p = IOBlackBox->imageData();
	end = p + spp * nbpix;

	while (p != end) {
	    val = *p++;
	    val += *p++;
	    val += *p++;

	    theHisto[val/3]++;
	}

    }

    maxval = 0;
    for (i = 0 ; i < 256 ; i++)
	if (theHisto[i] > maxval)
	    maxval= theHisto[i];

    return;
}
