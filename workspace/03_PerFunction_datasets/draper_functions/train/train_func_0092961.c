dareval(v,k,x)
vari *v;
INT k;
double *x;
{ arstruct *rt;
    rt = viptr(v,k);
    switch (rt->cmd)
    { case 'e': return(0.0);
        case 'v': return(vitem(rt->vv,0));
        case 'O': return(rt->f(dareval(v,rt->nx[0],x),dareval(v,rt->nx[1],x)));
        case 'P': return(rt->f(0.0,dareval(v,rt->nx[1],x)));
        case 'D': return(rt->x);
        case 'G': return(rt->f());
        case 'H': return(rt->f(dareval(v,rt->nx[1],x)));
        case 'f': return(rt->f(dareval(v,rt->nx[0],x)));
        case 'M': return(rsample(vareval(v,rt->nx[0])));
        case 'x': return(x[rt->m]);
        case 'U': return(vitem(vareval(v,rt->nx[0]),(int)dareval(v,rt->nx[1],x)-1));
        case 'Q': ERROR(("sequence in dareval"));
            return(0.0);
        default : ERROR(("dareval: unknown command %c",rt->cmd));
    }
    return(0.0);
}
