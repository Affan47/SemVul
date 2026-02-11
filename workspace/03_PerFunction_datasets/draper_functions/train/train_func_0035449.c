ajBuffreadLineStore(AjPFilebuff buff, AjPStr* Pdest,
                           AjBool dostore, AjPStr *Pstore)
{
    ajlong fpos = 0;
    AjBool ret;

    ret =  ajBuffreadLinePos(buff, Pdest, &fpos);

    if(dostore && ret)
    {
	ajDebug("ajBuffreadLineStore: '%S'", *Pdest);
	ajStrAppendS(Pstore,*Pdest);
    }

    return ret;
}
