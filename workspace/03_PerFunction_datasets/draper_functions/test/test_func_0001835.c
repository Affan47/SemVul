P_Port_Filedescriptor(Object port) {
    Check_Type(port, T_Port);
    if ((PORT(port)->flags & (P_STRING|P_OPEN)) != P_OPEN)
        Primitive_Error("~s: invalid port", port);
    return Make_Integer(fileno(PORT(port)->file));
}
