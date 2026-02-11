read_image_pgmCmd()
{
#ifdef DEBUG_READ
	printf("in read image pgm\n");
#endif
	chars_read = 0;

	if (!image_range_exists()) {
		err("First `set image range'");
		return false;
	}
#if 0
	if (!_dataFILE.back().get_type()) {
		err("Can only read images from binary files");
		demonstrate_command_usage();
		return false;
	}
#endif
	switch (_nword) {
	case 3:
		if (!read_pgm_image(_dataFILE.back().get_fp(), &_image, &_imageMask)) {
			blank_image();
			blank_imageMask();
			return false;
		} else {
			PUT_VAR("..image_width..",  double(_image.ras_width));
			PUT_VAR("..image_height..", double(_image.ras_height));
			return maybe_make_grids();
		}

	case 8:
		if (4 == get_cmd_values(_word, _nword, "box", 4, _dstack)) {
			define_image_scales(_dstack[0], _dstack[1], _dstack[2], _dstack[3]);
		} else {
			err("Cannot read `box' parameters");
			demonstrate_command_usage();
			return false;
		}
		if (!read_pgm_image(_dataFILE.back().get_fp(), &_image, &_imageMask)) {
			blank_image();
			blank_imageMask();
			return false;
		} else {
			PUT_VAR("..image_width..", double(_image.ras_width));
			PUT_VAR("..image_height..", double(_image.ras_height));
			return maybe_make_grids();
		}

	default:
		NUMBER_WORDS_ERROR;
		demonstrate_command_usage();
		return false;
	}

}
