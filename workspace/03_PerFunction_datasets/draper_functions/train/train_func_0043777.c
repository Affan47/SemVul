P_Output_Portp (Object x) {
    return TYPE(x) == T_Port && IS_OUTPUT(x) ? True : False;
}
