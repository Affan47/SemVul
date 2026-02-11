PrimitiveODestroy(ClientData cd) {
  XOTclObject *obj = (XOTclObject*)cd;
  Tcl_Interp *interp;


  assert(obj && !(obj->flags & XOTCL_DESTROYED));


  PRINTOBJ("PrimitiveODestroy", obj);

  if (!obj || !obj->teardown) return;
  interp = obj->teardown;


  if (Tcl_InterpDeleted(interp)) return;


  if (!(obj->flags & XOTCL_DESTROY_CALLED)) {
    callDestroyMethod(cd, interp, obj, 0);
    obj->id = NULL;
  }

#ifdef OBJDELETION_TRACE
  fprintf(stderr,"  physical delete of %p id=%p destroyCalled=%d '%s'\n",
          obj, obj->id, (obj->flags & XOTCL_DESTROY_CALLED), ObjStr(obj->cmdName));
#endif

  CleanupDestroyObject(interp, obj, 0);

  while (obj->mixinStack)
    MixinStackPop(obj);

  while (obj->filterStack)
    FilterStackPop(obj);

  obj->teardown = NULL;

#if 0
  {


    Tcl_Command cmd = Tcl_FindCommand(interp, ObjStr(obj->cmdName), 0, 0);
    if (cmd)
      Tcl_Command_deleteProc(cmd) = NULL;
  }
#endif

  if (obj->nsPtr) {

    XOTcl_DeleteNamespace(interp, obj->nsPtr);
    obj->nsPtr = NULL;
  }


  obj->flags |= XOTCL_DESTROYED;
  objTrace("ODestroy", obj);
#if REFCOUNT_TRACE
  fprintf(stderr,"ODestroy %p flags %d rc %d destr %d dc %d\n",
          obj, obj->flags,
          (obj->flags & XOTCL_REFCOUNTED) != 0,
          (obj->flags & XOTCL_DESTROYED) != 0,
          (obj->flags & XOTCL_DESTROY_CALLED) != 0
          );
#endif
#if REFCOUNTED
  if (!(obj->flags & XOTCL_REFCOUNTED)) {
    DECR_REF_COUNT(obj->cmdName);
  }
#else
  DECR_REF_COUNT(obj->cmdName);
#endif

  XOTclCleanupObject(obj);

#if !defined(NDEBUG)
  if (obj != (XOTclObject*)RUNTIME_STATE(interp)->theClass)
    checkAllInstances(interp, RUNTIME_STATE(interp)->theClass, 0);
#endif
}
