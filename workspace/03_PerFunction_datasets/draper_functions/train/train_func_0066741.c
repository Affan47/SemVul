findQualTycon(id)
Cell id; {
    if (!isPair(id)) internal("findQualTycon");
    switch (fst(id)) {
	case CONIDCELL :
	case CONOPCELL :
	    return findTycon(textOf(id));
	case QUALIDENT : {
	    Text   t  = qtextOf(id);
	    List   ms = findQualifiers(qmodOf(id));
	    if (isNull(ms)) return NIL;
	    while (nonNull(ms)) {
	      Module m  = hd(ms);
	      List   es = NIL;
	      ms = tl(ms);
	      if (m == currentModule) {
		es = module(m).tycons;
	      } else {
		es = getModuleImports(m);
	      }
	      for(; nonNull(es); es=tl(es)) {
		Cell e = hd(es);
		if (isTycon(e) && tycon(e).text==t)
		  return e;
		if (isPair(e) && isTycon(fst(e)) &&  tycon(fst(e)).text==t)
		  return fst(e);
	      }
	    }
	    return NIL;
	}
	default : internal("findQualTycon2");
    }
    return NIL;
}
