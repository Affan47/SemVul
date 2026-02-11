HandleMessage(nMessage &message){
    static tArray<bool> warned;


    nCurrentSenderID currentSender( message.SenderID() );

#ifdef DEBUG_X
    if (message.descriptor>1)
        con << "RMT " << message.descriptor << "\n";
#endif

#ifndef NOEXCEPT
    try{
#endif
        nDescriptor *nd = 0;


        if ( message.descriptor  < MAXDESCRIPTORS )
            nd=descriptors[message.descriptor];

        if (nd){
            if ((message.SenderID() <= MAXCLIENTS) || nd->acceptWithoutLogin)
                nd->handler(message);
        }
        else
            if (!warned[message.Descriptor()]){
                tOutput warn;
                warn.SetTemplateParameter(1, message.Descriptor());
                warn << "$network_warn_unknowndescriptor";
                con << warn;
                warned[message.Descriptor()]=true;
            }
#ifndef NOEXCEPT
    }
    catch(nIgnore const &){

    }
    catch(nKillHim const &){

        con << tOutput("$network_error");
        sn_DisconnectUser(message.SenderID(), "$network_kill_error" );
    }

#endif
}
