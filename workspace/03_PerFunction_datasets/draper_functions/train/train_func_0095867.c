print_objv(interp,objc,objv)
Tcl_Interp *interp;
int objc;
Tcl_Obj *objv[];
{
    char **argv;
    int argc;
    int len;
    argv = (char **)ckalloc(objc+1 * sizeof(char *));
    for (argc=0 ; argc<objc ; argc++) {
	argv[argc] = Tcl_GetStringFromObj(objv[argc],&len);
    }
    argv[argc] = NULL;
    return(print_argv(interp,argc,argv));
}
