prepareDictDirs()
{
	userDictDirs = splitString(cfg->getString("DataDir", ""), DICT_DIR_DELIMITER);

	defaultDictDirs = splitString( DICT_DIR, DICT_DIR_DELIMITER );


	if(userDictDirs.size() == 0) {
		dictDirs = defaultDictDirs;
	} else {
		dictDirs = userDictDirs;
	}


}
