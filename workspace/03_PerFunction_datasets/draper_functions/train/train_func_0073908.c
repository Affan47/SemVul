gola_fixup(LexState *ls, FuncScope *bl)
{
  VarInfo *v = ls->vstack + bl->vstart;
  VarInfo *ve = ls->vstack + ls->vtop;
  for (; v < ve; v++) {
    GCstr *name = strref(v->name);
    if (name != NULL) {
      if (gola_islabel(v)) {
	VarInfo *vg;
	setgcrefnull(v->name);
	for (vg = v+1; vg < ve; vg++)
	  if (strref(vg->name) == name && gola_isgoto(vg)) {
	    if ((bl->flags&FSCOPE_UPVAL) && vg->slot > v->slot)
	      gola_close(ls, vg);
	    gola_patch(ls, vg, v);
	  }
      } else if (gola_isgoto(v)) {
	if (bl->prev) {
	  bl->prev->flags |= name == NAME_BREAK ? FSCOPE_BREAK : FSCOPE_GOLA;
	  v->slot = bl->nactvar;
	  if ((bl->flags & FSCOPE_UPVAL))
	    gola_close(ls, v);
	} else {
	  ls->linenumber = ls->fs->bcbase[v->startpc].line;
	  if (name == NAME_BREAK)
	    lj_lex_error(ls, 0, LJ_ERR_XBREAK);
	  else
	    lj_lex_error(ls, 0, LJ_ERR_XLUNDEF, strdata(name));
	}
      }
    }
  }
}
