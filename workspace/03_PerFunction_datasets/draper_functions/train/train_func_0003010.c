mkspecnode(fun,argptr,k)
truc fun;
truc *argptr;
int k;
{
    struct opnode *node;
    int flg;
    truc obj;

    flg = (k == 1 ? fSPECIAL1 : fSPECIAL2);
    obj = newobj(flg,SIZEOFOPNODE(k),(trucptr *)&node);
    node->op = fun;
    node->arg0 = argptr[0];
    if(k == 2)
        node->arg1 = argptr[1];
    return(obj);
}
