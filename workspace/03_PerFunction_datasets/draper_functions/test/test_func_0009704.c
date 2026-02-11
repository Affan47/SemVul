print(char*s,...)
{va_list p;va_start(p,s);
if(term_line_empty&& *s=='\n')++s;
vprintf(s,p);va_end(p);
term_line_empty=s[strlen(s)-1]=='\n';update_terminal();
}
