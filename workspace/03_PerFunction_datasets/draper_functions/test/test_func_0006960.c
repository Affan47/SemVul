tclISF_main(ClientData clientData, Tcl_Interp *interp,
                int objc, Tcl_Obj *CONST objv[])
{
    const char * cmd = NULL;
    int cmd_length = 0,
        err = TCL_OK;

    if (objc < 2)
    {
        Tcl_WrongNumArgs(interp, 1, objv, "save filename strokes_list drawingAttributes_list \n fortify filename");
        return TCL_ERROR;
    }


    cmd = Tcl_GetStringFromObj(objv[1], &cmd_length);
    if (strcmp(cmd, "save")==0)
        err = tclISF_save(clientData,interp,objc-1, objv+1);
    else if (strcmp(cmd, "fortify")==0)
        err = tclISF_fortify(clientData,interp,objc-1,objv+1);
    else {
        Tcl_WrongNumArgs(interp, 1, objv, "save filename strokes_list drawingAttributes_list \n fortify filename");
        return TCL_ERROR;
    }

    return err;
}
