allocVars(Absyn *program, Table *globalTable, boolean showVarAlloc) {

  Entry *e;
  e = lookup(globalTable, newSym("exit"));
  e->u.procEntry.size_args_out   = 0;
  e->u.procEntry.size_local_vars = PREDEF_PROC;

  e = lookup(globalTable, newSym("time"));
  e->u.procEntry.size_args_out   = 0;
  e->u.procEntry.size_local_vars = PREDEF_PROC;

  e = lookup(globalTable, newSym("readi"));
  e->u.procEntry.size_args_out   = 0;
  e->u.procEntry.size_local_vars = PREDEF_PROC;

  e = lookup(globalTable, newSym("readc"));
  e->u.procEntry.size_args_out   = 0;
  e->u.procEntry.size_local_vars = PREDEF_PROC;

  e = lookup(globalTable, newSym("printi"));
  e->u.procEntry.size_args_out   = 0;
  e->u.procEntry.size_local_vars = PREDEF_PROC;

  e = lookup(globalTable, newSym("printc"));
  e->u.procEntry.size_args_out   = 0;
  e->u.procEntry.size_local_vars = PREDEF_PROC;

  e = lookup(globalTable, newSym("clearAll"));
  e->u.procEntry.size_args_out   = 0;
  e->u.procEntry.size_local_vars = PREDEF_PROC;

  e = lookup(globalTable, newSym("setPixel"));
  e->u.procEntry.size_args_out   = 0;
  e->u.procEntry.size_local_vars = PREDEF_PROC;

  e = lookup(globalTable, newSym("drawCircle"));
  e->u.procEntry.size_args_out   = 0;
  e->u.procEntry.size_local_vars = PREDEF_PROC;

  e = lookup(globalTable, newSym("drawLine"));
  e->u.procEntry.size_args_out   = 0;
  e->u.procEntry.size_local_vars = PREDEF_PROC;


  compute_procs(globalTable, globalTable->bintree);

  compute_procs(globalTable, globalTable->bintree);


  if(showVarAlloc) {
    show_VarAlloc(globalTable->bintree);
  }
}
