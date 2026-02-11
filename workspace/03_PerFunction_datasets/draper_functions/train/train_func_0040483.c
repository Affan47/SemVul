findCopy(const SoFieldContainer *orig,
			   SbBool copyConnections)


{
    if (! copyDictList || ! (*copyDictList)[0])
	return NULL;

    SbDict *copyDict = (SbDict *) (*copyDictList)[0];

    void *copyPtr;
    if (! copyDict->find((unsigned long) orig, copyPtr))
	return NULL;

    SoFieldContainer *copyFC = (SoFieldContainer *) copyPtr;


    if (! copyFC->notifyEnabled) {
	copyFC->notifyEnabled = TRUE;
	copyFC->copyContents(orig, copyConnections);
    }

    return copyFC;
}
