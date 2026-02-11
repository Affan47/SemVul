findQualName(id)
Cell id; {
    if (!isPair(id))
	internal("findQualName");
    switch (fst(id)) {
	case VARIDCELL :
	case VAROPCELL :
	case CONIDCELL :
	case CONOPCELL :
	    return findName(textOf(id));
	case QUALIDENT : {
	    Text   t  = qtextOf(id);
	    List  ms  = findQualifiers(qmodOf(id));
	    if (isNull(ms)) return NIL;
	    while (nonNull(ms)) {
	      Module m  = hd(ms);
	      List   es = NIL;
	      ms = tl(ms);
	      if (m == currentModule) {
		es = module(m).names;
	      } else {
		es = getModuleImports(m);
	      }
	      for(; nonNull(es); es=tl(es)) {
		Cell e = hd(es);
		if (isName(e) && name(e).text==t)
		    return e;
		if (isTycon(e) && tycon(e).text==t)
		    return e;
		else if (isPair(e)) {
		    List subentities = NIL;
		    Cell c = fst(e);
		    if (snd(e) == DOTDOT) {
			if (isTycon(c)
			    && (tycon(c).what==DATATYPE || tycon(c).what==NEWTYPE)) {
			    subentities = tycon(c).defn;
			} else if (isClass(c))
			    subentities = cclass(c).members;
		    } else {
			subentities = snd(e);
		    }
		    for(; nonNull(subentities); subentities=tl(subentities)) {
			if (name(hd(subentities)).text == t)
			    return hd(subentities);
		    }
		}
	      }
	    }
	    return NIL;
	}
	default : internal("findQualName2");
    }
    return NIL;
}
