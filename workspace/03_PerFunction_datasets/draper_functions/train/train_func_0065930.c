set_xyzlabel(text_label *label)
{
    char *text = NULL;

    c_token++;
    if (END_OF_COMMAND) {
	free(label->text);
	label->text = NULL;
	return;
    }

    parse_label_options(label);

    if (!END_OF_COMMAND) {
	text = try_to_get_string();
	if (text) {
	    free(label->text);
	    label->text = text;
	}
#ifdef BACKWARDS_COMPATIBLE
	if (isanumber(c_token) || equals(c_token, "-")) {

	    get_position_default(&(label->offset),character);
	}
#endif
    }

    parse_label_options(label);

}
