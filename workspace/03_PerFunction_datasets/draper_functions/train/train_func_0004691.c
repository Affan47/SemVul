statements(strom,endptr)
truc *strom;
truc *endptr;
{
    truc obj;
    int tok;
    int n = 0;

    while(1) {
        tok = skipeoltok(strom);
        if(tok == SEMICOLTOK) {
            nexttok(strom,1);
            continue;
        }
        else if(tok == SYMBOLTOK) {
            if(lookupsym(SymBuf,endptr) == sDELIM) {
                nexttok(strom,0);
                break;
            }
        }
        obj = readexpr(strom,0);
        if(obj == parserrsym || obj == breaksym) {
            PARSnpop(n);
            return(aERROR);
        }
        else if(obj == enddotsym) {
            break;
        }
        else {
            PARSpush(obj);
            n++;
        }
    }
    return(n);
}
