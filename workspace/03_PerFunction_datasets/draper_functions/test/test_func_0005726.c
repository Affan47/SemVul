Set ( str seq )

{
    if (seq && *seq)
    {
        str tmp;

        sequence.Set(seq);

        if (topnode) delete topnode, topnode = NULL;

        tmp = sequence.Compressed();

        if (tmp) topnode = new PtNode(tmp,NULL,0,0), delete tmp;
    }
}
