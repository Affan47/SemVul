printValue (FILE *fp, value *v, int indent)
{
  int i ;

  for (i = 0 ; i < indent ; i++)
    fputc (' ',fp) ;

  switch (v->type)
    {
      case intval:
        fprintf (fp,"%s : %ld # INTEGER\n",v->name,v->v.int_val) ;
        break ;

      case stringval:
        fprintf (fp,"%s : \"",v->name) ;
        {
          char *p = v->v.charp_val ;
          while (*p)
            {
              if (*p == '"' || *p == '\\')
                fputc ('\\',fp) ;
              fputc (*p,fp) ;
              p++ ;
            }
        }
        fprintf (fp,"\" # STRING\n") ;
        break ;

      case charval:
        fprintf (fp,"%s : %c",v->name,047) ;
        switch (v->v.char_val)
          {
            case '\\':
              fprintf (fp,"\\\\") ;
              break ;

            default:
              if (isprint((unsigned char) v->v.char_val))
                fprintf (fp,"%c",v->v.char_val) ;
              else
                fprintf (fp,"\\%03o",v->v.char_val) ;
          }
        fprintf (fp,"%c # CHARACTER\n",047) ;
        break ;

      case realval:
        fprintf (fp,"%s : %f # REAL\n",v->name,v->v.real_val) ;
        break ;

      case boolval:
        fprintf (fp,"%s : %s # BOOLEAN\n",
                 v->name,(v->v.bool_val ? "true" : "false")) ;
        break ;

      case scopeval:
        fprintf (fp,"%s %s { # SCOPE\n",v->v.scope_val->scope_type,v->name) ;
        printScope (fp,v->v.scope_val,indent + 5) ;
        for (i = 0 ; i < indent ; i++)
          fputc (' ',fp) ;
        fprintf (fp,"}\n") ;
        break ;

      default:
        fprintf (fp,"UNKNOWN value type: %d\n",v->type) ;
        exit (1) ;
    }
}
