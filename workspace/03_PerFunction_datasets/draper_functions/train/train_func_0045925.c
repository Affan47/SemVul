Ackt(unsigned short id,unsigned short peer){
#ifdef DEBUG_X
    int success=0;
#endif
    for(int i=sn_pendingAcks.Len()-1;i>=0;i--){
        nWaitForAck * ack = sn_pendingAcks(i);
        if (ack->message->MessageID()==id &&
                ack->receiver==peer){
#ifdef DEBUG


#endif

#ifdef DEBUG_X
            success=1;

            if (ack->message->descriptor>1)
                con << "AT  " << ack->message->descriptor << '\n';
#endif


            REAL thisping=netTime - ack->timeFirstSent;
            sn_Connections[peer].ping.Add( thisping, 1/(1 + 10 * REAL(ack->timeouts * ack->timeouts * ack->timeouts ) ) );

            ack->AckExtraAction();
            delete ack;
            ::timeouts[peer]=0;
            if (i<sn_pendingAcks.Len()-1) i++;
        }
    }

#ifdef DEBUG_X
    if (!success && peer!=MAXCLIENTS+1)
    {
        con << "Ack " << id << ':' << peer << " was not asked for.\n";
        if (sn_pendingAcks.Len()) con << "Expected:\n";
        for(int i=sn_pendingAcks.Len()-1;i>=0;i--){
            con << i << "\t:"
            << sn_pendingAcks[i]->message->messageIDBig_ << ":"
            << sn_pendingAcks[i]->receiver << '\n';
        }
    }
#endif
}
