ConnectToServerCore(nServerInfoBase *server)
{
    tASSERT( server );

    ePlayerNetID::ClearAll();


    gSettingsReverter reverter;

    sn_bigBrotherString = renderer_identification;

    nNetObject::ClearAll();

    just_connected=true;

    rViewport::Update(MAX_PLAYERS);


    bool to=sr_textOut;

    {
#ifndef DEDICATED
    rSysDep::SwapGL();
    rSysDep::ClearGL();
    rSysDep::SwapGL();
    rSysDep::ClearGL();
    eSoundLocker locker;
#endif

    sr_con.autoDisplayAtNewline=true;
    sr_con.fullscreen=true;

    sr_textOut=true;

    tOutput o;

    nConnectError error = nOK;

    nNetObject::ClearAll();

    o.SetTemplateParameter(1, server->GetName());
    o << "$network_connecting_to_server";
    con << o;
    error = server->Connect();

    switch (error)
    {
    case nABORT:
        return false;
        break;
    case nOK:
        break;
    case nTIMEOUT:
        sg_NetworkError("$network_message_timeout_title", "$network_message_timeout_inter", 20);
        return false;
        break;

    case nDENIED:
        sg_NetworkError("$network_message_denied_title", sn_DenyReason.Len() > 2 ? "$network_message_denied_inter2" : "$network_message_denied_inter", 20);
        return false;
        break;
    }
    }


    if (sn_GetNetState()==nCLIENT){
        REAL endTime=tSysTimeFloat()+30;
        con << tOutput("$network_connecting_gamestate");
        while (!sg_currentGame && tSysTimeFloat()<endTime && (sn_GetNetState() != nSTANDALONE)){
            tAdvanceFrame();
            sg_Receive();
            nNetObject::SyncAll();
            tAdvanceFrame();
            sn_SendPlanned();
            st_DoToDo();

#ifndef DEDICATED
            rSysDep::SwapGL();
            rSysDep::ClearGL();
#endif

            sn_Delay();
        }
        if (sg_currentGame){
            sr_con.autoDisplayAtNewline=false;
            sr_con.fullscreen=false;

            con << tOutput("$network_syncing_gamestate");
            sg_EnterGame( nCLIENT );
        }
        else{

            sg_NetworkError("$network_message_lateto_title", "$network_message_lateto_inter", 20);
        }
    }

    bool ret = true;

    sn_SetNetState(nSTANDALONE);

    sg_currentGame = NULL;
    nNetObject::ClearAll();
    ePlayerNetID::ClearAll();

    if (!sg_RequestedDisconnection && uMenu::quickexit != uMenu::QuickExit_Total )
    {
        sg_StopQuickExit();

        switch (sn_GetLastError())
        {
        case nOK:
            ret = sg_NetworkError("$network_message_abortconn_title",
                                  "$network_message_abortconn_inter", 20);
            break;
        default:
            ret = sg_NetworkError("$network_message_lostconn_title",
                                  "$network_message_lostconn_inter", 20);
            break;
        }
    }

    sr_con.autoDisplayAtNewline=false;
    sr_con.fullscreen=false;

    sr_textOut=to;

    return ret;
}
