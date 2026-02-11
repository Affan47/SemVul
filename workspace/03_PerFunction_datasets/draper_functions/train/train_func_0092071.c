set_size()
{
    c_token++;
    if (END_OF_COMMAND) {
	xsize = 1.0;
	ysize = 1.0;
    } else {
	if (almost_equals(c_token, "sq$uare")) {
	    aspect_ratio = 1.0;
	    ++c_token;
	} else if (almost_equals(c_token,"ra$tio")) {
	    ++c_token;
	    aspect_ratio = real_expression();
	} else if (almost_equals(c_token, "nora$tio") || almost_equals(c_token, "nosq$uare")) {
	    aspect_ratio = 0.0;
	    ++c_token;
	}

	if (!END_OF_COMMAND) {
	    xsize = real_expression();
	    if (equals(c_token,",")) {
		c_token++;
		ysize = real_expression();
	    } else {
		ysize = xsize;
	    }
	}
    }
    if (xsize <= 0 || ysize <=0) {
	xsize = ysize = 1.0;
	int_error(NO_CARET,"Illegal value for size");
    }
}
