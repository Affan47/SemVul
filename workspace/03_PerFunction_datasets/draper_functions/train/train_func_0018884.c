printslashstring(scheme *sc, char *p, int len) {
  int i;
  unsigned char *s=(unsigned char*)p;
  putcharacter(sc,'"');
  for ( i=0; i<len; i++) {
    if(*s==0xff || *s=='"' || *s<' ' || *s=='\\') {
      putcharacter(sc,'\\');
      switch(*s) {
      case '"':
	putcharacter(sc,'"');
	break;
      case '\n':
	putcharacter(sc,'n');
	break;
      case '\t':
	putcharacter(sc,'t');
	break;
      case '\r':
	putcharacter(sc,'r');
	break;
      case '\\':
	putcharacter(sc,'\\');
	break;
      default: {
	  int d=*s/16;
	  putcharacter(sc,'x');
	  if(d<10) {
	    putcharacter(sc,d+'0');
	  } else {
	    putcharacter(sc,d-10+'A');
	  }
	  d=*s%16;
	  if(d<10) {
	    putcharacter(sc,d+'0');
	  } else {
	    putcharacter(sc,d-10+'A');
	  }
	}
      }
    } else {
      putcharacter(sc,*s);
    }
    s++;
  }
  putcharacter(sc,'"');
}
