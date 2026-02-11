mainparse()
{
  char *pos;
  comment_match_t comment;
  char temp[TEMP_SIZE];
  char outline[TEMP_SIZE];
  int  skipline = 0;

  syntaxlist_t *mainsyntax = findSyntax("main");

  pos = tempstr;
  findComment(pos, comment);
  if (comment.at) {
    char quote_char = '"';
    char* quote1 = strchr(pos, quote_char);
    char* quote2;
    while (quote1 && quote1 < comment.at) {
      quote2 = strchr(quote1+1, quote_char);
      if (!quote2) {
	comment.at = 0;
	break;
      }
      if (quote2 > comment.at) {
	findComment(quote2, comment);
	quote1 = strchr(quote2+1, quote_char);
      }
    }

    if (comment.at)
      *comment.at = '\0';
  }

  *outline = '\0';

  pos = str_skipspace(pos);
  basepos = pos-tempstr;
  if (!str_empty(pos)) {
    if (!str_parse(mainsyntax, pos, temp)) {
      fprintf(stderr,"WARNING, Line %d: no syntax match: \"%s\"\n",
	      current_line,tempstr);
      printf("MISMATCH: \"%s\"\n",tempstr);
      return;
    }
    if (str_empty(temp))
      skipline = 1;
    else if (flags & FLAG_INLINEMODE) {
      str_addatpos(outline, "\"", basepos);
      strcat(outline, temp);
      str_addatpos(outline, "\\n\\t\"", basepos+29);
    } else
      str_addatpos(outline, temp, basepos);
  }

  if (comment.at) {

    *comment.at = comment.data->src[0];

    CommentConvert(comment.at, *comment.data);
    str_addatpos(outline, comment.at, comment.at-tempstr);
  }

  if (!skipline || comment.at)
    printf("%s\n",outline);
}
