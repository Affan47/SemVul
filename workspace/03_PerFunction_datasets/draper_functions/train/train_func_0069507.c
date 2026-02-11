send_pdu(Connection *conn, Octstr *id, SMPP_PDU *pdu)
{
    Octstr *os;
    int ret;

    dump_pdu("Sending PDU:", id, pdu);
    os = smpp_pdu_pack(pdu);
    if (os)
        ret = conn_write(conn, os);
    else
	ret = -1;
    octstr_destroy(os);
    return ret;
}
