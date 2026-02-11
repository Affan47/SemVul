CmdIgnoreLet(int code)


{
    char t[100];
    char cThis;
    int i;
    char *s;

    s = getSimpleCommand();

    cThis = getNonBlank();
    if (cThis == '=')
        cThis = getNonBlank();

    t[0] = cThis;
    for (i=1; i<100; i++) {
        t[i] = getTexChar();
        if (t[i]==' ' || t[i]=='\n') break;
    }
    t[i]='\0';

    newDefinition(s+1,NULL,t,0);
    free(s);
}
