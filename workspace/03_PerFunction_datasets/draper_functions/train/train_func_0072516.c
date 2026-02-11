leaveDirectory(int haveError)
{
	if(!currentDir)
		return;

	if (!haveError) {
		if(dirPath && dirPath != emptyString)
			free(dynDirPath);
		if(wide)
			putchar('\n');

		if(!concise)
			printSummary(filesInDir, bytesInDir);
	}
	FREE(&currentDir);
}
