load_gle_code_sub(const char* name, CmdLineObj& cmdline) throw(ParserError) {
	string in_name = name;
	GLERC<GLEScript> script = new GLEScript();
	GLEFileLocation* loc = script->getLocation();
	loc->fromFileNameDir(in_name, GLE_WORKING_DIR);
	script->getSource()->load();
	return script;
}
