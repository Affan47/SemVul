Dbg_On(interp,immediate)
Tcl_Interp *interp;
int immediate;


{
	if (!debugger_active) init_debugger(interp);


	debug_cmd = step;
	step_count = 1;

#define LITERAL(s) Tcl_NewStringObj ((s), sizeof(s)-1)

	if (immediate) {
	Tcl_Obj* fake_cmd = LITERAL ( "--interrupted-- (command_unknown)");

	Tcl_IncrRefCount (fake_cmd);
	debugger_trap((ClientData)0,interp,-1,Tcl_GetString (fake_cmd),0,1,&fake_cmd);

	Tcl_DecrRefCount (fake_cmd);
	}
}
