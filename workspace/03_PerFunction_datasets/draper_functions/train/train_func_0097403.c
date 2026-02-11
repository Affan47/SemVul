P_Keysym_To_String (Object k) {
    register char *s;

    s = XKeysymToString ((KeySym)Get_Long (k));
    return s ? Make_String (s, strlen (s)) : False;
}
