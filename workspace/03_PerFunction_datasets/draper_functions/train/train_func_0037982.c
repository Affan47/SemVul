xaccSplitOrder (const Split *sa, const Split *sb)
{
    int retval;
    int comp;
    char *da, *db;
    gboolean action_for_num;

    if (sa == sb) return 0;

    if (!sa) return -1;
    if (!sb) return +1;


    action_for_num = qof_book_use_split_action_for_num_field
                                                        (xaccSplitGetBook (sa));
    if (action_for_num)
        retval = xaccTransOrder_num_action (sa->parent, sa->action,
                                            sb->parent, sb->action);
    else
        retval = xaccTransOrder (sa->parent, sb->parent);
    if (retval) return retval;


    da = sa->memo ? sa->memo : "";
    db = sb->memo ? sb->memo : "";
    retval = g_utf8_collate (da, db);
    if (retval)
        return retval;


    da = sa->action ? sa->action : "";
    db = sb->action ? sb->action : "";
    retval = g_utf8_collate (da, db);
    if (retval != 0)
        return retval;


    if (sa->reconciled < sb->reconciled) return -1;
    if (sa->reconciled > sb->reconciled) return +1;


    comp = gnc_numeric_compare(xaccSplitGetAmount(sa), xaccSplitGetAmount (sb));
    if (comp < 0) return -1;
    if (comp > 0) return +1;

    comp = gnc_numeric_compare(xaccSplitGetValue(sa), xaccSplitGetValue (sb));
    if (comp < 0) return -1;
    if (comp > 0) return +1;


    DATE_CMP(sa, sb, date_reconciled);


    retval = qof_instance_guid_compare(sa, sb);
    if (retval) return retval;

    return 0;
}
