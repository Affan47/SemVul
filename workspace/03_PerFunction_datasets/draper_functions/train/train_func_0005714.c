_font(Request& r, MethodParams& params) {
	const String& alphabet=params.as_string(0, "alphabet must not be code");
	size_t alphabet_length=alphabet.length(r.charsets.source());
	if(!alphabet_length)
		throw Exception(PARSER_RUNTIME,
			0,
			"alphabet must not be empty");

	gdImage* image=load(r, params.as_string(1, FILE_NAME_MUST_NOT_BE_CODE));

	int spacebar_width=image->SX();
	int monospace_width=0;
	int letter_spacing=1;
	if(params.count()>2){
		if(HashStringValue* options=params[2].get_hash()){

			if(params.count()>3)
				throw Exception(PARSER_RUNTIME, 0, "too many params were specified");
			int valid_options=0;
			if(Value* vspacebar_width=options->get(spacebar_width_name)){
				valid_options++;
				spacebar_width=r.process_to_value(*vspacebar_width).as_int();
			}
			if(Value* vmonospace_width=options->get(monospace_width_name)){
				valid_options++;
				monospace_width=r.process_to_value(*vmonospace_width).as_int();
				if(!monospace_width)
					monospace_width=image->SX();
			}
			if(Value* vletter_spacing=options->get(letter_spacing_name)){
				valid_options++;
				letter_spacing=r.process_to_value(*vletter_spacing).as_int();
			}
			if(valid_options!=options->count())
				throw Exception(PARSER_RUNTIME, 0, CALLED_WITH_INVALID_OPTION);
		} else {

			spacebar_width=params.as_int(2, "param must be int or hash", r);
			if(params.count()>3) {
				monospace_width=params.as_int(3, "monospace_width must be int", r);
				if(!monospace_width)
					monospace_width=image->SX();
			}
		}
	}

	if(int remainder=image->SY() % alphabet_length)
		throw Exception(PARSER_RUNTIME,
			0,
			"font-file height(%d) not divisable by alphabet size(%d), remainder=%d",
				image->SY(), alphabet_length, remainder);

	GET_SELF(r, VImage).set_font(new Font(
		r.charsets.source(),
		alphabet,
		image,
		image->SY() / alphabet_length, monospace_width, spacebar_width, letter_spacing));
}
