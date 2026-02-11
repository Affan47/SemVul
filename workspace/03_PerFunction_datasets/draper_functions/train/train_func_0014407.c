FuncIO_pipe(Obj self)
{
    Obj tmp;
    int fds[2];
    int res;

    res = pipe(fds);
    if (res == -1) {
        SySetErrorNo();
        return Fail;
    }
    tmp = NEW_PREC(0);
    AssPRec(tmp,RNamName("toread"),INTOBJ_INT(fds[0]));
    AssPRec(tmp,RNamName("towrite"),INTOBJ_INT(fds[1]));
    return tmp;
}
