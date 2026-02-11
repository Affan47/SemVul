embPatPushHit(AjPList l, const AjPStr name, ajuint pos, ajuint plen,
		   ajuint begin, ajuint mm)
{
    EmbPMatMatch hit;

    AJNEW0(hit);

    hit->seqname = ajStrNewS(name);
    hit->len = plen;
    hit->cod = ajStrNew();
    hit->pat = ajStrNew();
    hit->acc = ajStrNew();
    hit->tit = ajStrNew();
    hit->start = pos+begin;
    hit->mm = mm;
    hit->end = pos+begin+plen-1;
    if(hit->start <= hit->end)
        hit->forward = ajTrue;
    ajListPush(l,(void *) hit);

    return;
}
