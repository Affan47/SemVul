SWIG_Tcl_NewInstanceObj(Tcl_Interp *interp, void *thisvalue, swig_type_info *type, int flags) {
  Tcl_Obj *robj = SWIG_NewPointerObj(thisvalue, type,0);

  if (thisvalue && (type->clientdata) && (interp)) {
    Tcl_CmdInfo    ci;
    char          *name;
    name = Tcl_GetStringFromObj(robj,NULL);
    if (!Tcl_GetCommandInfo(interp,name, &ci) || (flags)) {
      swig_instance *newinst = (swig_instance *) malloc(sizeof(swig_instance));
      newinst->thisptr = Tcl_DuplicateObj(robj);
      Tcl_IncrRefCount(newinst->thisptr);
      newinst->thisvalue = thisvalue;
      newinst->classptr = (swig_class *) type->clientdata;
      newinst->destroy = flags;
      newinst->cmdtok = Tcl_CreateObjCommand(interp, Tcl_GetStringFromObj(robj,NULL), (swig_wrapper_func) SWIG_MethodCommand, (ClientData) newinst, (swig_delete_func) SWIG_ObjectDelete);
      if (flags) {
        SWIG_Acquire(thisvalue);
      }
    }
  }
  return robj;
}
