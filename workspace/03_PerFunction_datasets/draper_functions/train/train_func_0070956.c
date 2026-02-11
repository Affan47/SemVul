RawImageGetRow(rawImageRec *raw, unsigned char *buf, int y, int z)
{
    unsigned char *iPtr, *oPtr, pixel;
    int count;

    if ((raw->type & 0xFF00) == 0x0100) {
	fseek(raw->file, raw->rowStart[y+z*raw->sizeY], SEEK_SET);
	fread(raw->tmp, 1, (unsigned int)raw->rowSize[y+z*raw->sizeY],
	      raw->file);

	iPtr = raw->tmp;
	oPtr = buf;
	while (1) {
	    pixel = *iPtr++;
	    count = (int)(pixel & 0x7F);
	    if (!count) {
		return;
	    }
	    if (pixel & 0x80) {
		while (count--) {
		    *oPtr++ = *iPtr++;
		}
	    } else {
		pixel = *iPtr++;
		while (count--) {
		    *oPtr++ = pixel;
		}
	    }
	}
    } else {
	fseek(raw->file, 512+(y*raw->sizeX)+(z*raw->sizeX*raw->sizeY),
	      SEEK_SET);
	fread(buf, 1, raw->sizeX, raw->file);
    }
}
