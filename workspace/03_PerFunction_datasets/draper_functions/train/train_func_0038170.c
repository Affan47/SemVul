GiveBigServerInfoCommon(nMessage &m, const nServerInfo & info, nDescriptor& descriptor )
{

    nMessage *ret = tNEW(nMessage)( descriptor );


    info.NetWrite( *ret );


    ret->ClearMessageID();
    ret->SendImmediately(m.SenderID(), false);
    nMessage::SendCollected(m.SenderID());
}
