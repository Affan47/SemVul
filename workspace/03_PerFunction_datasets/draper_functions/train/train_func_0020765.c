getwords()
{
	char	words[80], *wptr;

	fputc('>', stdout);
	word1[0] = word2[0] = '\0';
	fflush(stdout);
	if (NULL == fgets(words, 80, stdin))
		exit(0);
	wptr = words;
	while (*wptr = tolower(*wptr))
		++wptr;
	sscanf(words, "%19s %19s", word1, word2);
	if (dbugflg)
		printf("WORD1 = %s, WORD2 = %s\n", word1, word2);
	return;
}
