String_Eval(char *expr) {
    Object str, res;
    char *p;
    GC_Node;
    static char buf[1024];

    str = Make_String(expr, strlen(expr));
    PORT(in)->name = str;
    PORT(in)->ptr = 0;
    res = General_Read(in, 0);
    GC_Link(res);
    res = Eval(res);
    (void)General_Print_Object(res, out, 1);
    str = P_Get_Output_String(out);
    p = Get_String(str);
    if (strlen(p) > sizeof buf - 1)
        p = "too long";
    strcpy(buf, p);
    GC_Unlink;
    return buf;
}
