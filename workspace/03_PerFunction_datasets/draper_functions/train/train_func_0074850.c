sn_SendPlanned2( REAL dt ){

    for(int i=0;i<=MAXCLIENTS+1;i++){
        nConnectionInfo & connection = sn_Connections[i];
        if ( connection.socket )
        {
            if (connection.sendBuffer_.Len()>0 && connection.bandwidthControl_.CanSend() )
                nMessage::SendCollected(i);


            connection.Timestep( dt );
        }
    }
}
