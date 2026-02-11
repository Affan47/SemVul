isBoxPatternOp(Tree box, Node& n, Tree& t1, Tree& t2)
{
    if (    isBoxPar(box, t1, t2) ||
            isBoxSeq(box, t1, t2) ||
            isBoxSplit(box, t1, t2) ||
            isBoxMerge(box, t1, t2) ||
            isBoxRec(box, t1, t2)    )
    {
        n = box->node();
        return true;
    } else {
        return false;
    }
}
