ktest_empty_cred_enc_part(krb5_cred_enc_part *cep)
{
    if (cep->s_address)
        ktest_destroy_address(&cep->s_address);
    if (cep->r_address)
        ktest_destroy_address(&cep->r_address);
    if (cep->ticket_info)
        ktest_destroy_sequence_of_cred_info(&cep->ticket_info);
}
