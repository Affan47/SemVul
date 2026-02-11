returnTypeAnnotation(Node *n)
  {
    String *ret=0;
    Parm *p = Getattr(n, "parms");
    String *tm;


    while (p) {
      if ((tm=Getattr(p, "tmap:argout:match_type"))) {
        tm = SwigType_str(tm, 0);
	if (ret)
          Printv(ret, ", ", tm, NULL);
        else
          ret = tm;
        p = Getattr(p, "tmap:argout:next");
      } else {
	p = nextSibling(p);
      }
    }


    if (!ret) {
      ret = Getattr(n, "type");
      if (ret) ret = SwigType_str(ret, 0);
    }
    return (ret && py3) ? NewStringf(" -> \"%s\" ", ret)
                        : NewString("");
  }
