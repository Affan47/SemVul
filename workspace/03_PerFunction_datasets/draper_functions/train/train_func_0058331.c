loan_assistant_data_init( LoanAssistantData *ldd )
{
    int i, optCount;
    RepayOptData *optData;


    for ( optCount = 0; REPAY_DEFAULTS[optCount].name != NULL; optCount++ )
        ;

    ldd->currentIdx = -1;

    ldd->ld.principal = gnc_numeric_zero();
    ldd->ld.startDate = g_date_new();
    ldd->ld.varStartDate = g_date_new();
    gnc_gdate_set_time64( ldd->ld.startDate, gnc_time (NULL) );
    ldd->ld.loan_schedule = NULL;
    ldd->ld.repayment_schedule = NULL;
    {
        Recurrence *r = g_new0(Recurrence, 1);
        recurrenceSet(r, 1, PERIOD_MONTH, ldd->ld.startDate, WEEKEND_ADJ_NONE);
        ldd->ld.repayment_schedule = g_list_append(ldd->ld.repayment_schedule, r);
    }

    ldd->ld.repMemo = g_strdup( _("Loan") );
    ldd->ld.repAmount = NULL;
    ldd->ld.repStartDate = g_date_new();
    ldd->ld.repayOptCount = optCount;
    ldd->ld.repayOpts = g_new0( RepayOptData*, optCount );

    ldd->repayOptsUI = g_new0( RepayOptUIData*, optCount );
    for ( i = 0; i < optCount; i++ )
    {
        g_assert( REPAY_DEFAULTS[i].name != NULL );

        ldd->repayOptsUI[i] = g_new0( RepayOptUIData, 1 );
        ldd->repayOptsUI[i]->ldd = ldd;

        optData = ldd->ld.repayOpts[i]
                  = ldd->repayOptsUI[i]->optData
                    = g_new0( RepayOptData, 1 );

        optData->enabled        = FALSE;
        optData->optValid	= FALSE;
        optData->FreqUniq	= FALSE;
        optData->name           = g_strdup( _(REPAY_DEFAULTS[i].name) );
        optData->txnMemo        = g_strdup( _(REPAY_DEFAULTS[i].
                                              defaultTxnMemo) );
        optData->amount         = 0.0;
        optData->throughEscrowP = REPAY_DEFAULTS[i].escrowDefault;
        optData->specSrcAcctP   = REPAY_DEFAULTS[i].specSrcAcctDefault;
        optData->schedule       = NULL;
        optData->startDate      = NULL;
    }
}
