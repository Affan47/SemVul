process_diff_control (string, db)
     char **string;
     struct diff_block *db;
{
  char *s = *string;
  int holdnum;
  enum diff_type type;


#define	SKIPWHITE(s)	{ while (*s == ' ' || *s == '\t') s++; }
#define	READNUM(s, num)	\
	{ unsigned char c = *s; if (!ISDIGIT (c)) return ERROR; holdnum = 0; \
	  do { holdnum = (c - '0' + holdnum * 10); }	\
	  while (ISDIGIT (c = *++s)); (num) = holdnum; }


  SKIPWHITE (s);
  READNUM (s, db->ranges[0][START]);


  SKIPWHITE (s);
  if (*s == ',')
    {

      s++;
      READNUM (s, db->ranges[0][END]);
    }
  else
    db->ranges[0][END] = db->ranges[0][START];


  SKIPWHITE (s);
  switch (*s)
    {
    case 'a':
      type = ADD;
      break;
    case 'c':
      type = CHANGE;
      break;
    case 'd':
      type = DELETE;
      break;
    default:
      return ERROR;
    }
  s++;


  SKIPWHITE (s);
  READNUM (s, db->ranges[1][START]);


  SKIPWHITE (s);
  if (*s == ',')
    {

      s++;
      READNUM (s, db->ranges[1][END]);
      SKIPWHITE (s);
    }
  else
    db->ranges[1][END] = db->ranges[1][START];

  *string = s;
  return type;
}
