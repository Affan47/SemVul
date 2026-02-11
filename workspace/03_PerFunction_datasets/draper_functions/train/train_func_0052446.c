at2_convertpdu(Octstr *pdutext)
{
    Octstr *pdu;
    int i;
    int len = octstr_len(pdutext);

    pdu = octstr_create("");
    for (i = 0; i < len; i += 2) {
        octstr_append_char(pdu, at2_hexchar(octstr_get_char(pdutext, i)) * 16
                           + at2_hexchar(octstr_get_char(pdutext, i + 1)));
    }
    return pdu;
}
