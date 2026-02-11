_LmSet(LmLighting *lgt, int a1, va_list *alist)
{
    int attr;

#define NEXT(type) va_arg(*alist, type)

    if (!alist) return lgt;
    if (lgt == NULL) {


      lgt =  OOGLNewE(LmLighting, "LmCreate Lighting");
      LmDefault(lgt);
    }

    for(attr = a1; attr != LM_END; attr = NEXT(int)) {
      switch (attr) {
      case LM_LtSet:
	LmAddLight(lgt, _LtSet(NULL, va_arg(*alist, int), alist));
	break;
      case LM_LIGHT:
	LmAddLight(lgt, NEXT(LtLight *));
	break;
      case LM_REPLACELIGHTS:
	if (NEXT(int))
	  lgt->valid |= LMF_REPLACELIGHTS;
	else
	  lgt->valid &= ~LMF_REPLACELIGHTS;
	break;
      case LM_AMBIENT:
	lgt->ambient = *NEXT(Color *);
	lgt->valid |= LMF_AMBIENT;
	break;
      case LM_LOCALVIEWER:
	lgt->localviewer = NEXT(int);
	lgt->valid |= LMF_LOCALVIEWER;
	break;
      case LM_ATTENC:
	lgt->attenconst = NEXT(double);
	lgt->valid |= LMF_ATTENC;
	break;
      case LM_ATTENM:
	lgt->attenmult = NEXT(double);
	lgt->valid |= LMF_ATTENM;
	break;
      case LM_OVERRIDE:
	lgt->override |= NEXT(int);
	break;
      case LM_NOOVERRIDE:
	lgt->override &= ~NEXT(int);
	break;
      case LM_INVALID:
	lgt->valid &= ~NEXT(int);
	break;
      default:
	OOGLError (0, "_LmSet: undefined option: %d\n", attr);
	return NULL;
	break;
      }
    }

    return lgt;

#undef NEXT
}
