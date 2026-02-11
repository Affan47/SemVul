dobindings(LVAL list, LVAL env)
{
    LVAL bnd, val;
    LVAL sym = NULL;


    xlsave1(val);


    for (; consp(list); list = cdr(list)) {


        bnd = car(list);


        if (symbolp(bnd)) {
            sym = bnd;
            val = NIL;
        }


        else if (consp(bnd)) {
            sym = match(SYMBOL,&bnd);
            val = evarg(&bnd);
        }
        else
            xlfail("bad binding");


        xlpbind(sym,val,env);
    }


    xlpop();
}
