merge_splits (Split *sa, Split *sb)
{
    Account *act;
    Transaction *txn;
    gnc_numeric amt, val;

    act = xaccSplitGetAccount (sb);
    xaccAccountBeginEdit (act);

    txn = sa->parent;
    xaccTransBeginEdit (txn);


    remove_guids (sa, sb);


    amt = xaccSplitGetAmount (sa);
    amt = gnc_numeric_add_fixed (amt, xaccSplitGetAmount (sb));
    xaccSplitSetAmount (sa, amt);

    val = xaccSplitGetValue (sa);
    val = gnc_numeric_add_fixed (val, xaccSplitGetValue (sb));
    xaccSplitSetValue (sa, val);


    xaccSplitSetReconcile (sa, NREC);


    if ((sb->gains_split) &&
            (sb->gains_split->gains & GAINS_STATUS_GAINS))
    {
        Transaction *t = sb->gains_split->parent;
        xaccTransBeginEdit (t);
        xaccTransDestroy (t);
        xaccTransCommitEdit (t);
    }


    xaccSplitDestroy(sb);

    xaccTransCommitEdit (txn);
    xaccAccountCommitEdit (act);
}
