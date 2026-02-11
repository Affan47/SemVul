wv_ugch(ch)


int ch;
{

 if (ch==EOL) {wf_chr(&f_t,EOL); return;}


 if (!isascprn(ch))
    {
     wf_wr(&f_t,"$\\bullet$");
     return;
    }

 switch (ch)
   {


    case '\"':  wf_wr(&f_t,"\\char`\\\"");  break;
    case '#':  wf_wr(&f_t,"\\#");  break;
    case '$':  wf_wr(&f_t,"\\$");  break;

    case '%':  wf_chr(&f_t,'\\'); wf_chr(&f_t,'%'); break;
    case '&':  wf_wr(&f_t,"\\&");  break;


    case '<': if (literal)
                 wf_wr(&f_t,"\\char`\\<");
              else
                 wf_wr(&f_t,"$<$");
              break;

    case '>': if (literal)
                 wf_wr(&f_t,"\\char`\\>");
              else
                 wf_wr(&f_t,"$>$");
              break;


    case '\\': if (literal)
                  wf_wr(&f_t,"\\char`\\\\");
               else
                  wf_wr(&f_t,"$\\backslash$");
               break;

    case '^':  wf_wr(&f_t,"\\char`\\^");  break;
    case '_':  wf_wr(&f_t,"\\_");  break;


    case '{':  if (literal)
                  wf_wr(&f_t,"\\char`\\{");
               else
                  wf_wr(&f_t,"$\\{$");
               break;
    case '|':  if (literal)
                  wf_wr(&f_t,"\\char`\\|");
               else
                  wf_wr(&f_t,"$|$");
               break;
    case '}':  if (literal)
                  wf_wr(&f_t,"\\char`\\}");
               else
                  wf_wr(&f_t,"$\\}$");
               break;
    case '~':  wf_wr(&f_t,"\\char`\\~");  break;
    default:   wf_chr(&f_t,ch);    break;
   }
}
