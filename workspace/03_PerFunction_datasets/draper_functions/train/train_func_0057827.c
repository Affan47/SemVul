P_Char_Upper_Casep (Object c) {
    Check_Type (c, T_Character);
    return isupper (CHAR(c)) ? True : False;
}
