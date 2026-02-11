setCompression(int format)
{
    static const Fl_Menu_Item noCompressionMenu[] = {
	{"None", 0, 0},
	{0}
    };
    static const Fl_Menu_Item binaryTiffCompression[] = {
	{"None", 0, (Fl_Callback *)chosencompression_cb, (void *)TIFF_CMP_NONE},
	{"LZW", 0, (Fl_Callback *)chosencompression_cb, (void *)TIFF_CMP_LZW},
	{"PackBits", 0, (Fl_Callback *)chosencompression_cb, (void *)TIFF_CMP_PACKBITS},
	{"Group 3", 0, (Fl_Callback *)chosencompression_cb, (void *)TIFF_CMP_CCITTG3},
	{"Group 4", 0, (Fl_Callback *)chosencompression_cb, (void *)TIFF_CMP_CCITTG4},
	{"RLE", 0, (Fl_Callback *)chosencompression_cb, (void *)TIFF_CMP_RLE},
	{"RLEW", 0, (Fl_Callback *)chosencompression_cb, (void *)TIFF_CMP_RLEW},
	{"Thunderscan", 0, (Fl_Callback *)chosencompression_cb, (void *)TIFF_CMP_THUNDER},
	{0}
    };
    static const Fl_Menu_Item greyTiffCompression[] = {
	{"None", 0, (Fl_Callback *)chosencompression_cb, (void *)TIFF_CMP_NONE},
	{"LZW", 0, (Fl_Callback *)chosencompression_cb, (void *)TIFF_CMP_LZW},
	{"PackBits", 0, (Fl_Callback *)chosencompression_cb, (void *)TIFF_CMP_PACKBITS},
	{0}
    };

    dbgprintf("Setting up the Choice buttons\n");
    switch (format) {
      case TIFF_FMT:
	compressionChoice->activate();
	compressionChoice->labelcolor(FL_BLACK);
	compressionChoice->textcolor(FL_BLACK);
	if (IOBlackBox->getCurrImgPixType() == IM_BINARY) {
	    compressionChoice->menu(binaryTiffCompression);
	    compressionChoice->value(latestBinaryTiffOption);
	} else {
	    compressionChoice->menu(greyTiffCompression);
	    compressionChoice->value(latestGreyTiffOption);
	}
	saveWindow->redraw();
	break;

      case ZIMAGE_FMT:
      case PNG_FMT:
      case JPG_FMT:
	compressionChoice->menu(noCompressionMenu);
	compressionChoice->deactivate();
	compressionChoice->labelcolor(40);
	compressionChoice->textcolor(40);
	saveWindow->redraw();
	break;

      default:
	dbgprintf("Unknown file format\n");
	compressionChoice->menu(noCompressionMenu);
	compressionChoice->deactivate();
	compressionChoice->labelcolor(40);
	compressionChoice->textcolor(40);
	saveWindow->redraw();
	break;
    }


    return;
}
