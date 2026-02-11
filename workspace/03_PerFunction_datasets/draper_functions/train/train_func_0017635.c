skipFilters(FILE *f, byte numfilters)
{
	while(numfilters--) {
		int filter = fgetc(f);
		switch(filter){
			case FILTER_DROPSHADOW:
				skipProtected(f, 23);
				break;
			case FILTER_BLUR:
				skipProtected(f, 9);
				break;
			case FILTER_GLOW:
				skipProtected(f, 15);
				break;
			case FILTER_BEVEL:
				skipProtected(f, 27);
				break;
			case FILTER_GRADIENTGLOW:
				skipProtected(f, fgetc(f)*5 + 19);
				break;
			case FILTER_ADJUSTCOLOR:
				skipProtected(f, 80);
				break;
			case FILTER_GRADIENTBEVEL:
				skipProtected(f, fgetc(f)*5 + 19);
				break;
			default:
				tellUser(1, "Unknown filter %i", filter);
		}
	}
}
