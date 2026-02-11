fixupBootNeuterArgs(Volume* volume, char unlockBaseband, char selfDestruct, char use39, char use46) {
	const char bootNeuterPlist[] = "/System/Library/LaunchDaemons/com.devteam.bootneuter.auto.plist";
	AbstractFile* plistFile;
	char* plist;
	Dictionary* info;
	size_t bufferSize;
	ArrayValue* arguments;

	XLOG(0, "fixing up BootNeuter arguments...\n");

	plist = malloc(1);
	bufferSize = 0;
	plistFile = createAbstractFileFromMemoryFile((void**)&plist, &bufferSize);
	get_hfs(volume, bootNeuterPlist, plistFile);
	plistFile->close(plistFile);
	info = createRoot(plist);
	free(plist);

	arguments = (ArrayValue*) getValueByKey(info, "ProgramArguments");
	addStringToArray(arguments, "-autoMode");
	addStringToArray(arguments, "YES");
	addStringToArray(arguments, "-RegisterForSystemEvents");
	addStringToArray(arguments, "YES");

	if(unlockBaseband) {
		addStringToArray(arguments, "-unlockBaseband");
		addStringToArray(arguments, "YES");
	}

	if(selfDestruct) {
		addStringToArray(arguments, "-selfDestruct");
		addStringToArray(arguments, "YES");
	}

	if(use39) {
		addStringToArray(arguments, "-bootLoader");
		addStringToArray(arguments, "3.9");
	} else if(use46) {
		addStringToArray(arguments, "-bootLoader");
		addStringToArray(arguments, "4.6");
	}

	plist = getXmlFromRoot(info);
	releaseDictionary(info);

	plistFile = createAbstractFileFromMemory((void**)&plist, sizeof(char) * strlen(plist));
	add_hfs(volume, plistFile, bootNeuterPlist);
	free(plist);
}
