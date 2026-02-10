lex_unget_char(LEX *lf)
{
   if (lf->ch == L_EOL) {
      lf->ch = 0;
   } else {
      lf->col_no--;
   }

}
