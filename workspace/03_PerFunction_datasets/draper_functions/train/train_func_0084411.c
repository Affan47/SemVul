Set(FilePath const &directory, FilePath const &name) {
	if (name.IsAbsolute()) {
		fileName = name.fileName;
	} else {
		fileName = directory.fileName;
		fileName.appendwithseparator(name.fileName.c_str(),
			fileName.endswith(pathSepString) ? '\0' : pathSepChar);
	}
}
