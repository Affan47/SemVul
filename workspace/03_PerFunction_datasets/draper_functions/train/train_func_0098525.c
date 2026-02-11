transcribe(Parser p, int back, int count)
{
    ExpandBuf(p->pbuf, p->pbufnext + count);
    memcpy(p->pbuf + p->pbufnext,
	   p->source->line + p->source->next - back,
	   count * sizeof(Char));
    p->pbufnext += count;
    return 0;
}
