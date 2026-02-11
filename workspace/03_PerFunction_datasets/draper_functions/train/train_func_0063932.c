getListEl(CliGameList *gl, int gNum, Str *out)  {
  switch(gl->games[gNum].state)  {
  case cliGame_noGame:
    str_copyCharsLen(out, "", 0);
    break;
  case cliGame_over:
    str_print(out, "\t-\t%s [%s]\tvs.\t%s [%s]\t%d\t%d\t%d\t%g\t\t%s",
	      str_chars(&gl->games[gNum].wName),
	      str_chars(&gl->games[gNum].wRank),
	      str_chars(&gl->games[gNum].bName),
	      str_chars(&gl->games[gNum].bRank),
	      gl->games[gNum].moveNum,
	      gl->games[gNum].size,
	      gl->games[gNum].handicap, gl->games[gNum].komi,
	      str_chars(&gl->games[gNum].flags));
    break;
  default:
    str_print(out, "\t%d\t%s [%s]\tvs.\t%s [%s]\t%d\t%d\t%d\t%g\t%s\t(%d)",
	      gNum,
	      str_chars(&gl->games[gNum].wName),
	      str_chars(&gl->games[gNum].wRank),
	      str_chars(&gl->games[gNum].bName),
	      str_chars(&gl->games[gNum].bRank),
	      gl->games[gNum].moveNum,
	      gl->games[gNum].size,
	      gl->games[gNum].handicap, gl->games[gNum].komi,
	      str_chars(&gl->games[gNum].flags),
	      gl->games[gNum].observers);
    break;
  }
}
