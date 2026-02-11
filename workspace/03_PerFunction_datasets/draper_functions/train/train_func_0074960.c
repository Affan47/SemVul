xaccTransSetTxnType (Transaction *trans, char type)
{
    char s[2] = {type, '\0'};
    g_return_if_fail(trans);
    xaccTransBeginEdit(trans);
    kvp_frame_set_str (trans->inst.kvp_data, TRANS_TXN_TYPE_KVP, s);
    qof_instance_set_dirty(QOF_INSTANCE(trans));
    xaccTransCommitEdit(trans);
}
