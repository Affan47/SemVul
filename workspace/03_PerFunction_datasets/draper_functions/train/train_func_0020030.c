newGLEFile(const char* glecode, const char* tmpfile) {
	GLERC<GLEScript> script;
	try {
		string in_name = tmpfile;
		script = new GLEScript();
		GLEFileLocation* loc = script->getLocation();
		loc->fromFileNameDir(in_name, GLE_WORKING_DIR);
		GLESourceFile* file = script->getSource()->getMainFile();
		char_separator sep("\n");
		tokenizer<char_separator> tokens(glecode, sep);
		while (tokens.has_more()) {
			string line = tokens.next_token();
			str_trim_both(line);
			GLESourceLine* sline = file->addLine();
			sline->setCode(line);
		}
		file->trim(1);
		script->getSource()->initFromMain();
	} catch (ParserError err) {
		string err_str;
		err.toString(err_str);
		str_uppercase_initial_capital(err_str);
		g_message(err_str);
	}
	return script;
}
