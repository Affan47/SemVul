GetScoreFromDisconnectedCopy()
{
    int i;

    for(i=se_PlayerNetIDs.Len()-1;i>=0;i--){
        ePlayerNetID *pni=se_PlayerNetIDs(i);
        if (pni->disconnected && pni->GetUserName() == GetUserName() && pni->Owner() == 0)
        {
#ifdef DEBUG
            con << GetName() << " reconnected.\n";
#endif

            pni->RequestSync();
            RequestSync();

            score = pni->score;

            ControlObject(pni->Object());

            pni->object = NULL;

            if (bool(object))
                chatting_ = true;

            pni->disconnected = false;
            se_PlayerNetIDs.Remove(pni, pni->listID);
            se_PlayerReferences.Remove( pni );
        }
    }
}
