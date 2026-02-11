convertTemplate(char *template, int n1, int n2, int n3, char **pname)
{
    char        s1[20], s2[20], s3[20];
    char       *t;

    sprintf(s1, "%1d", n1);
    sprintf(s2, "%1d", n2);
    sprintf(s3, "%1d", n3);

    *pname = t = (char *) HDmalloc(HDstrlen(template) + 61);

    while (*template)
        switch (*template)
          {
              case TEMPLATE_CHAR1:
                  fillTemplate(&template, &t, s1, TEMPLATE_CHAR1);
                  break;
              case TEMPLATE_CHAR2:
                  fillTemplate(&template, &t, s2, TEMPLATE_CHAR2);
                  break;
              case TEMPLATE_CHAR3:
                  fillTemplate(&template, &t, s3, TEMPLATE_CHAR3);
                  break;
              default:
                  *t++ = *template++;
          }
    *t = '\0';
}
