setTclObjValue(Tcl_Obj*& value_obj, const bool value)
{


  if (value_obj == NULL) {
    value_obj = Tcl_NewBooleanObj(0);
  }


  Tcl_SetBooleanObj(value_obj, value);
}
