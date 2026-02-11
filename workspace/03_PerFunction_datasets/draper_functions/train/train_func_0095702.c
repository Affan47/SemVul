noEmptySequence(vector<Sequence> seqVector, string *offendingSeq)
{
    vector<Sequence>::iterator si;
    for (si = seqVector.begin(); si != seqVector.end(); si++) {
        if (si->isEmpty()) {
            offendingSeq->assign(si->getName());
            return false;
        }
    }
    return true;
}
