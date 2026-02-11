HandleMailReturnToSender(WorldPacket& recv_data)
{
    ObjectGuid mailboxGuid;
    uint32 mailId;
    recv_data >> mailboxGuid;
    recv_data >> mailId;
    recv_data.read_skip<uint64>();

    if (!CheckMailBox(mailboxGuid))
        return;

    Player* pl = _player;
    Mail* m = pl->GetMail(mailId);
    if (!m || m->state == MAIL_STATE_DELETED || m->deliver_time > time(NULL))
    {
        pl->SendMailResult(mailId, MAIL_RETURNED_TO_SENDER, MAIL_ERR_INTERNAL_ERROR);
        return;
    }


    CharacterDatabase.BeginTransaction();
    CharacterDatabase.PExecute("DELETE FROM mail WHERE id = '%u'", mailId);

    CharacterDatabase.PExecute("DELETE FROM mail_items WHERE mail_id = '%u'", mailId);
    CharacterDatabase.CommitTransaction();
    pl->RemoveMail(mailId);


    if (m->messageType == MAIL_NORMAL && m->sender)
    {
        MailDraft draft;
        if (m->mailTemplateId)
            draft.SetMailTemplate(m->mailTemplateId, false);
        else
            draft.SetSubjectAndBody(m->subject, m->body);

        if (m->HasItems())
        {
            for (MailItemInfoVec::iterator itr2 = m->items.begin(); itr2 != m->items.end(); ++itr2)
            {
                if (Item* item = pl->GetMItem(itr2->item_guid))
                    draft.AddItem(item);

                pl->RemoveMItem(itr2->item_guid);
            }
        }

        draft.SetMoney(m->money).SendReturnToSender(GetAccountId(), m->receiverGuid, ObjectGuid(HIGHGUID_PLAYER, m->sender));
    }

    delete m;
    pl->SendMailResult(mailId, MAIL_RETURNED_TO_SENDER, MAIL_OK);
}
