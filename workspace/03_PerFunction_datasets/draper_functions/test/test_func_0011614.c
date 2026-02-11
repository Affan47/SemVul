qif_txn_invst_parse(QifContext ctx, GList *record)
{
    QifTxn txn;
    QifInvstTxn itxn;
    QifLine line;

    g_return_val_if_fail(ctx, QIF_E_INTERNAL);
    g_return_val_if_fail(record, QIF_E_BADSTATE);

    txn = qif_txn_new();
    txn->txn_type = ctx->parse_type;
    itxn = qif_invst_txn_new();
    txn->invst_info = itxn;

    for (; record; record = record->next)
    {
        line = record->data;

        switch (line->type)
        {
        case 'D':
            qif_save_str(txn->datestr);
            break;
        case 'P':
            qif_save_str(txn->payee);
            break;
        case 'N':
            itxn->action = qif_parse_action(line);
            break;
        case 'C':
            txn->cleared = qif_parse_cleared(line);
            break;
        case 'M':
            if (!txn->current_split)
                qif_save_str(txn->default_split->memo);
            break;
        case 'T':
            if (!qif_is_bad_numeric_string(line->line))
                qif_save_str(itxn->amountstr);
            break;
        case '$':
            if (!qif_is_bad_numeric_string(line->line))
                qif_save_str(itxn->d_amountstr);
            break;
        case 'I':
            qif_save_str(itxn->pricestr);
            break;
        case 'Q':
            qif_save_str(itxn->sharesstr);
            break;
        case 'Y':
            qif_save_str(itxn->security);
            break;
        case 'O':
            qif_save_str(itxn->commissionstr);
            break;
        case 'L':
            qif_save_str(itxn->catstr);
            break;
        default:
            PERR("Unknown QIF Investment transaction data at line %d: %s",
                 line->lineno, line->line);
        }
    }


    if (txn->datestr && itxn->action != QIF_A_NONE)
    {


        if (!itxn->security)
            itxn->security = g_strdup("");


        if (ctx->current_acct)
            txn->from_acct = ctx->current_acct;
        else
            qif_set_flag(ctx->parse_flags, QIF_F_ITXN_NEEDS_ACCT);


        ctx->parse_state = g_list_prepend(ctx->parse_state, txn);

    }
    else
    {

        qif_txn_destroy((QifObject)txn);
    }

    return QIF_E_OK;
}
