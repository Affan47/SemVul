P_Class_Existsp (Object name) {
    register CLASS_INFO *p;
    register char *s = Get_Strsym (name);

    for (p = ctab; p < clast; p++) {
        if (streq (p->name, s))
            return True;
    }
    return False;
}
