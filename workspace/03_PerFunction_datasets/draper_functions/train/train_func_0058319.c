loan_rep_page_save( GtkAssistant *assistant, gpointer user_data )
{
    LoanAssistantData *ldd = user_data;

    if ( ldd->ld.repMemo )
        g_free( ldd->ld.repMemo );
    ldd->ld.repMemo =
        gtk_editable_get_chars( GTK_EDITABLE(ldd->repTxnName), 0, -1 );

    if ( ldd->ld.repAmount )
        g_free( ldd->ld.repAmount );
    ldd->ld.repAmount =
        gtk_editable_get_chars( GTK_EDITABLE(ldd->repAmtEntry), 0, -1 );

    ldd->ld.repFromAcct =
        gnc_account_sel_get_account( ldd->repAssetsFromGAS );

    ldd->ld.repPriAcct =
        gnc_account_sel_get_account( ldd->repPrincToGAS );

    ldd->ld.repIntAcct =
        gnc_account_sel_get_account( ldd->repIntToGAS );

    recurrenceListFree(&ldd->ld.repayment_schedule);
    gnc_frequency_save_to_recurrence(ldd->repGncFreq,
                                     &ldd->ld.repayment_schedule,
                                     ldd->ld.repStartDate);
}
