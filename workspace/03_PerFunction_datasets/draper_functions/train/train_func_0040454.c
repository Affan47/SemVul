aclDumpRegexList(relist * data)
{
    wordlist *W = NULL;
    while (data != NULL) {
	wordlistAdd(&W, data->pattern);
	data = data->next;
    }
    return W;
}
