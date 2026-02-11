txn_transaction_cb(const AB_TRANSACTION *element, gpointer user_data)
{
    GncABImExContextImport *data = user_data;
    Transaction *gnc_trans;
    GncABTransType trans_type;

    g_return_val_if_fail(element && data, NULL);


    gnc_trans = gnc_ab_trans_to_gnc(element, data->gnc_acc);

    if (data->execute_txns && data->ab_acc)
    {
        AB_TRANSACTION *ab_trans = AB_Transaction_dup(element);
        AB_JOB *job;


        AB_Transaction_SetLocalBankCode(
            ab_trans, AB_Account_GetBankCode(data->ab_acc));
        AB_Transaction_SetLocalAccountNumber(
            ab_trans, AB_Account_GetAccountNumber(data->ab_acc));
        AB_Transaction_SetLocalCountry(ab_trans, "DE");


        switch (AB_Transaction_GetType(ab_trans))
        {
        case AB_Transaction_TypeDebitNote:
            trans_type = SINGLE_DEBITNOTE;
            break;
        case AB_Transaction_TypeEuTransfer:
            trans_type = SEPA_TRANSFER;
            break;
        case AB_Transaction_TypeTransaction:


        case AB_Transaction_TypeTransfer:
        default:
            trans_type = SINGLE_TRANSFER;
        }

        job = gnc_ab_get_trans_job(data->ab_acc, ab_trans, trans_type);


        if (!job || AB_Job_CheckAvailability(job
#ifndef AQBANKING_VERSION_5_PLUS
                                             , 0
#endif
                                            ))
        {

            if (gnc_verify_dialog(
                        NULL, FALSE, "%s",
                        _("The backend found an error during the preparation "
                          "of the job. It is not possible to execute this job. \n"
                          "\n"
                          "Most probably the bank does not support your chosen "
                          "job or your Online Banking account does not have the permission "
                          "to execute this job. More error messages might be "
                          "visible on your console log.\n"
                          "\n"
                          "Do you want to enter the job again?")))
            {
                gnc_error_dialog(NULL, "Sorry, not implemented yet. Please check the console or trace file logs to see which job was rejected.");
            }
        }
        else
        {
            gnc_gen_trans_list_add_trans_with_ref_id(data->generic_importer, gnc_trans, AB_Job_GetJobId(job));


            g_datalist_set_data(&data->tmp_job_list, gnc_AB_JOB_to_readable_string(job), job);
        }
        AB_Transaction_free(ab_trans);
    }
    else
    {

        gnc_gen_trans_list_add_trans(data->generic_importer, gnc_trans);
    }

    return NULL;
}
