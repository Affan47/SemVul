sgf_catComment(Sgf *sgf, const char *s)  {
  SgfElem  *se;

  se = sgfElem_findTypeInNode(sgf->active, sgfType_comment);
  if (se)  {
    str_catChars(se->sVal, s);
  } else  {
    sgf_addCElem(sgf, sgfType_comment, goStone_empty);
    sgf->active->sVal = str_createChars(s);
  }
}
