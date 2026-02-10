Snumval(symb)
truc symb;
{
    truc obj;
    char *str;
    unsigned len;
    int argn, count, tok;

    obj = eval(ARG1PTR(evalStkPtr));
    if(Tflag(obj) != fSTRING) {
        error(symb,err_str,obj);
        return(brkerr());
    }
    len = STRlen(obj);
    if(len >= strbufSize-3) {
        error(symb,err_2long,mkfixnum(len));
        return(brkerr());
    }
    str = STRING(obj);
    tok = numval(str,&count);
    if(symb == atoisym) {
        if(tok == INUMTOK)
            obj = mkint(Curnum.sign,Curnum.digits,Curnum.len);
        else {
            count = 0;
            obj = zero;
        }
    }
    else {
        if(tok != FLOATTOK)
            curfltprec = deffltprec();
        if(tok != FLOATTOK && tok != INUMTOK) {
            count = 0;
            obj = fltzero(curfltprec);
        }
        else {
            obj = mkfloat(curfltprec,&Curnum);
        }
    }
    argn = *ARGCOUNTPTR(evalStkPtr);
    if(argn == 2) {
        Lvalassign(ARGNPTR(evalStkPtr,2),mkfixnum(count));
    }
    return(obj);
}
