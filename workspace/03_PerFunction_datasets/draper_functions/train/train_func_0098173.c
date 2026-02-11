AHB_SWIFT_GetNextSubTag(const char **sptr, AHB_SWIFT_SUBTAG **tptr) {
  const char *s;
  int id=0;
  int nextId=0;
  const char *content=NULL;
  AHB_SWIFT_SUBTAG *stg;

  s=*sptr;
  if (*s=='?') {
    const char *t;

    t=s;
    t++;
    if (*t==0x0a)
      t++;
    if (*t && isdigit(*t)) {
      id=(*(t++)-'0')*10;
      if (*t==0x0a)
	t++;
      if (*t && isdigit(*t)) {
	id+=*(t++)-'0';
	s=t;
      }
    }
  }
  content=s;


  for (;;) {
    while(*s && *s!='?')
      s++;

    if (*s=='?') {
      const char *t;

      t=s;
      t++;
      if (*t==0x0a)
	t++;
      if (*t && isdigit(*t)) {
	nextId=(*(t++)-'0')*10;
	if (*t==0x0a)
	  t++;
	if (*t && isdigit(*t)) {
	  nextId+=*(t++)-'0';


	  break;
	}
        else {

          if (*s)
            s++;
          else

            break;
        }
      }
      else {

        if (*s)
          s++;
        else

          break;
      }
    }
    else if (*s)

      s++;
    else

      break;
  }


  stg=AHB_SWIFT_SubTag_new(id, content, s-content);


  *tptr=stg;
  *sptr=s;
  return 0;
}
