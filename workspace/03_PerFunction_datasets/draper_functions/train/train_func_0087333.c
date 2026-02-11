drawSchema(Tree bd, const char* projname, const char* dev)
{
	gDevSuffix 		= dev;
	sFoldingFlag 	= boxComplexity(bd) > gFoldThreshold;

	mkchdir(projname);

	scheduleDrawing(bd);

	Tree t; while (pendingDrawing(t)) {
		writeSchemaFile(t);
	}

	cholddir();
}
