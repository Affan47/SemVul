lnp_str_to_pdu(char* value, dchat_pdu_t* pdu)
{
    int lport;
    char* ptr;

    lport = (int) strtol(value, &ptr, 10);


    if (ptr[0] != '\0' || !is_valid_port(lport))
    {
        return -1;
    }

    pdu->lport = lport;
    return 0;
}
