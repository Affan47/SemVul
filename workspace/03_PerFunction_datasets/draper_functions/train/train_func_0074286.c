expPrintifyObj(obj)
    Tcl_Obj *obj;
{
    ThreadSpecificData *tsdPtr = TCL_TSD_INIT(&dataKey);


    if ((!tsdPtr->diagToStderr) && (!tsdPtr->diagChannel)) return((char *)0);

    return expPrintifyReal(Tcl_GetString(obj));
}
