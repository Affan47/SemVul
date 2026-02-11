fix_objnum(integer *objnum, word match,
		       int real_obj,
		       int actor, int dobj, int iobj)
{
  if (real_obj) *objnum=real_obj;
  else if (match==ext_code[wdobject]) *objnum=iobj;
  else if (match==ext_code[wdnoun]) *objnum=dobj;
  else if (match==ext_code[wdname]) *objnum=actor;
}
