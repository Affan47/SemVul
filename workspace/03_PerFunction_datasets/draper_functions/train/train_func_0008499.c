HandleMailMarkAsRead(WorldPacket& recv_data)
{
    ObjectGuid mailboxGuid;
    uint32 mailId;
    recv_data >> mailboxGuid;
    recv_data >> mailId;

    if (!CheckMailBox(mailboxGuid))
        { return; }

    Player* pl = _player;

    if (Mail* m = pl->GetMail(mailId))
    {
        if (pl->unReadMails)
            { --pl->unReadMails; }
        m->checked = m->checked | MAIL_CHECK_MASK_READ;
        pl->m_mailsUpdated = true;
        m->state = MAIL_STATE_CHANGED;
    }
}
