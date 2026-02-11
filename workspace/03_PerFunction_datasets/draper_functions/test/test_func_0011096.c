jpegscan(FILE *fp, int *mark, unsigned int *len, int first)
{
	infile = fp;


	if (first && topmkr() != JPEG_M_SOI) {
		exifwarn("doesn't appear to be a JPEG file; "
		    "searching for start of image");
		if (nxtmkr() != JPEG_M_SOI)
			exifdie("start of image not found");
	}


	for (;;) {
		switch ((*mark = nxtmkr())) {
		case JPEG_M_EOI:
		case JPEG_M_SOS:
			return (FALSE);

		case JPEG_M_APP1:
		case JPEG_M_APP2:
			*len = mkrlen();
			return (TRUE);


		case JPEG_M_SOF0:
		case JPEG_M_SOF1:
		case JPEG_M_SOF3:
		case JPEG_M_SOF5:
		case JPEG_M_SOF6:
		case JPEG_M_SOF7:
		case JPEG_M_SOF9:
		case JPEG_M_SOF10:
		case JPEG_M_SOF11:
		case JPEG_M_SOF13:
		case JPEG_M_SOF14:
		case JPEG_M_SOF15:
			sofmrk(*mark);
			break;


		default:
			skipmkr();
		}
	}

	return (FALSE);
}
