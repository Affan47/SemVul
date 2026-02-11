update_loc()
{
     char *p;

     for (p = strchr(yytext, '#')+1; *p && isspace(*p); p++)
	  ;
     if (p[0] == 'l')
	  p += 4;

     line_num = strtoul(p, &p, 10);
     for ( ; *p && isspace(*p); p++)
	  ;
     if (p[0] == '"') {
	  int n;

	  for (p++, n = 0; p[n] && p[n] != '"'; n++)
	       ;
	  obstack_grow(&string_stk, p, n);
	  obstack_1grow(&string_stk, 0);
	  filename = obstack_finish(&string_stk);
     }
     if (debug > 1)
	  printf(_("New location: %s:%d\n"), filename, line_num);
}
