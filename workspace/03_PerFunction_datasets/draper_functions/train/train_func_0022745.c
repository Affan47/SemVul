ParseEndFile(parse_t * parse)
{
	if (parse->pfile) {
		fclose(parse->pfile);
		parse->pfile = NULL;
		parse->inparsing = false;
		parse->nextline = false;
		parse->lnumber = 0;
	}
}
