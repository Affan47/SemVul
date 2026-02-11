xaccSplitReinit(Split * split)
{

    split->acc         = NULL;
    split->orig_acc    = NULL;
    split->parent      = NULL;
    split->lot         = NULL;

    CACHE_REPLACE(split->action, "");
    CACHE_REPLACE(split->memo, "");
    split->reconciled  = NREC;
    split->amount      = gnc_numeric_zero();
    split->value       = gnc_numeric_zero();

    split->date_reconciled.tv_sec  = 0;
    split->date_reconciled.tv_nsec = 0;

    split->balance             = gnc_numeric_zero();
    split->cleared_balance     = gnc_numeric_zero();
    split->reconciled_balance  = gnc_numeric_zero();

    if (split->inst.kvp_data)
        kvp_frame_delete(split->inst.kvp_data);
    split->inst.kvp_data = kvp_frame_new();
    qof_instance_set_idata(split, 0);

    split->gains = GAINS_STATUS_UNKNOWN;
    split->gains_split = NULL;
}
