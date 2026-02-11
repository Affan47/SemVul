xaccSplitClone (const Split *s)
{
    Split *split = g_object_new (GNC_TYPE_SPLIT, NULL);

    split->parent              = NULL;
    split->memo                = CACHE_INSERT(s->memo);
    split->action              = CACHE_INSERT(s->action);
    split->reconciled          = s->reconciled;
    split->date_reconciled     = s->date_reconciled;
    split->value               = s->value;
    split->amount              = s->amount;
    split->balance             = s->balance;
    split->cleared_balance     = s->cleared_balance;
    split->reconciled_balance  = s->reconciled_balance;

    split->gains = GAINS_STATUS_UNKNOWN;
    split->gains_split = NULL;

    qof_instance_init_data(&split->inst, GNC_ID_SPLIT, qof_instance_get_book(s));
    kvp_frame_delete(split->inst.kvp_data);
    split->inst.kvp_data = kvp_frame_copy(s->inst.kvp_data);

    xaccAccountInsertSplit(s->acc, split);
    if (s->lot)
    {

        gnc_lot_add_split(s->lot, split);
    }
    return split;
}
