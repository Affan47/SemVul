Itcl_ArgList(argc, arglist)
    int argc;
    CompiledLocal* arglist;
{
    char *val;
    Tcl_Obj *objPtr;
    Tcl_DString buffer;

    Tcl_DStringInit(&buffer);

    while (arglist && argc-- > 0) {
        if (arglist->defValuePtr) {
            val = Tcl_GetStringFromObj(arglist->defValuePtr, (int*)NULL);
            Tcl_DStringStartSublist(&buffer);
            Tcl_DStringAppendElement(&buffer, arglist->name);
            Tcl_DStringAppendElement(&buffer, val);
            Tcl_DStringEndSublist(&buffer);
        }
        else {
            Tcl_DStringAppendElement(&buffer, arglist->name);
        }
        arglist = arglist->nextPtr;
    }

    objPtr = Tcl_NewStringObj(Tcl_DStringValue(&buffer),
        Tcl_DStringLength(&buffer));

    Tcl_DStringFree(&buffer);

    return objPtr;
}
