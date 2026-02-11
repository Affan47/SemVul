jid_free(jid_t jid)
{
    if((jid->jid_data != NULL) && (jid->jid_data_len != 0))
        free(jid->jid_data);
    if (jid->_user != NULL )
        free(jid->_user);
    if (jid->_full != NULL )
        free(jid->_full);
    if (jid != NULL )
        free(jid);
}
