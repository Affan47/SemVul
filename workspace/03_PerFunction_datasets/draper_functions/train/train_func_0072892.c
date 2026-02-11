ajSeqsetGetseqNameC(const AjPSeqset seq, ajuint i)
{
    if(!seq)
        return "";

    if(i >= seq->Size)
	return "";

    if(seq->Seq[i]->Name)
        return MAJSTRGETPTR(seq->Seq[i]->Name);

    return "";
}
