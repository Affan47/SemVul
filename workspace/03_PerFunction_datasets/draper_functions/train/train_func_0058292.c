tok_line(t, indent)
struct token *t;
int indent;
   {
   int nxt_line;


   if (no_nl)
      return;
   if (t->flag & LineChk) {


      nxt_line = t->line;
      if (fname != t->fname  || line > nxt_line || line + 2 < nxt_line)
         line_dir(nxt_line, t->fname);
      else if (nl && line == nxt_line)
         line_dir(nxt_line, t->fname);
      else if (line != nxt_line) {
         nl = 1;
         --nxt_line;
         while (line < nxt_line) {
            putc('\n', out_file);
            ++line;
            }
         }
      }
   chk_nl(indent);
   }
