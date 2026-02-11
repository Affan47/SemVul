P_Char_To_Integer (Object c) {
    Check_Type (c, T_Character);
    return Make_Integer (CHAR(c));
}
