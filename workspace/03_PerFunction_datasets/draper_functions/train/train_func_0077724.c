generic_pipe(char *buf, int len, void *rock)
{
    struct generic_context_t *text = (struct generic_context_t *)rock;
    char *toWrite = NULL, *toSend = NULL;
    int toWriteLen = 0;
    char *lineEnd = NULL;
    int ret = IMTEST_OK;


    if(text->midLine) {
	text->midLine =
	    (char *)xrealloc(text->midLine, text->midLineLen+len+1);
	memcpy(text->midLine+text->midLineLen, buf, len);
	text->midLineLen += len;
	text->midLine[text->midLineLen] = '\0';

	toWrite = text->midLine;
	toWriteLen = text->midLineLen;
    } else {
	toWrite = buf;
	toWriteLen = len;
    }


    while(toWrite && (lineEnd = memchr(toWrite, '\n', toWriteLen)) != NULL) {
	size_t len_todo;

	len_todo = lineEnd - toWrite + 1;

	toSend = (char *)xrealloc(toSend, len_todo + 1);

	memcpy(toSend, toWrite, len_todo);
	toSend[len_todo] = '\0';

	ret = text->pipe_oneline(toSend, len_todo, text->rock);
	if(ret != IMTEST_OK) break;

	toWrite = lineEnd+1;
	toWriteLen -= len_todo;

	if(toWriteLen <= 0) toWrite = NULL;

    }

    if(toWrite && ret == IMTEST_OK) {
	char *newMidLine;

	newMidLine = (char *)xmalloc(toWriteLen);
	memcpy(newMidLine, toWrite, toWriteLen);
	if(text->midLine) free(text->midLine);
	text->midLine = newMidLine;
	text->midLineLen = toWriteLen;
    } else if (text->midLine || ret != IMTEST_OK) {
	free(text->midLine);
	text->midLine = NULL;
	text->midLineLen = 0;
    }

    free(toSend);
    return ret;
}
