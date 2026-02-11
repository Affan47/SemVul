SearchDirs (const char* path) {
    Directory dir(path);

    if (_verbose) {
	printf("recursively searching directory %s\n", path);
    }

    for (int i = 0; i < dir.Count(); ++i) {
        const char* file = dir.File(i);

        if (!DotOrDotDot(file)) {
            char filePath[MAXPATHLEN+1];
            strcpy(filePath, dir.Normalize(path));
            strcat(filePath, file);

            Search(filePath);
        }
    }
}
