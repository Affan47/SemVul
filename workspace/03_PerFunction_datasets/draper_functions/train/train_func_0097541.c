setReceiverUid(const QString &uid)
{
    if (uid.contains("@[]@")) {
        QStringList uids = uid.split("@[]@", QString::KeepEmptyParts);
        if (uids.count() == 2) {
            m_ReceiverFormUid = uids.at(0);
            m_ModeUid = uids.at(1);
        }
    } else {
        m_ReceiverFormUid = uid;
    }
}
