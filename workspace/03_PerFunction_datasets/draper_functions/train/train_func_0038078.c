parse_colorspec(struct t_colorspec *tc, int options)
{
    c_token++;
    if (END_OF_COMMAND)
	int_error(c_token, "expected colorspec");
    if (almost_equals(c_token,"def$ault")) {
	c_token++;
	tc->type = TC_DEFAULT;
    } else if (equals(c_token,"bgnd")) {
	c_token++;
	tc->type = TC_LT;
	tc->lt = LT_BACKGROUND;
    } else if (equals(c_token,"lt")) {
	c_token++;
	if (END_OF_COMMAND)
	    int_error(c_token, "expected linetype");
	tc->type = TC_LT;
	tc->lt = int_expression()-1;
	if (tc->lt < LT_BACKGROUND) {
	    tc->type = TC_DEFAULT;
	    int_warn(c_token,"illegal linetype");
	}
    } else if (options <= TC_LT) {
	tc->type = TC_DEFAULT;
	int_error(c_token, "only tc lt <n> possible here");
    } else if (equals(c_token,"ls") || almost_equals(c_token,"lines$tyle")) {
	c_token++;
	tc->type = TC_LINESTYLE;
	tc->lt = real_expression();
    } else if (almost_equals(c_token,"rgb$color")) {
	c_token++;
	tc->type = TC_RGB;
	if (almost_equals(c_token, "var$iable")) {
	    tc->value = -1.0;
	    c_token++;
	} else {
	    tc->value = 0.0;
	    tc->lt = parse_color_name();
	}
    } else if (almost_equals(c_token,"pal$ette")) {
	c_token++;
	if (equals(c_token,"z")) {

	    if (options >= TC_Z) {
		tc->type = TC_Z;
	    } else {
		tc->type = TC_DEFAULT;
		int_error(c_token, "palette z not possible here");
	    }
	    c_token++;
	} else if (equals(c_token,"cb")) {
	    tc->type = TC_CB;
	    c_token++;
	    if (END_OF_COMMAND)
		int_error(c_token, "expected cb value");
	    tc->value = real_expression();
	} else if (almost_equals(c_token,"frac$tion")) {
	    tc->type = TC_FRAC;
	    c_token++;
	    if (END_OF_COMMAND)
		int_error(c_token, "expected palette fraction");
	    tc->value = real_expression();
	    if (tc->value < 0. || tc->value > 1.0)
		int_error(c_token, "palette fraction out of range");
	} else {

	    if (options >= TC_Z)
		tc->type = TC_Z;
	}
    } else if (options >= TC_VARIABLE && almost_equals(c_token,"var$iable")) {
	tc->type = TC_VARIABLE;
	c_token++;
    } else {
	int_error(c_token, "colorspec option not recognized");
    }
}
