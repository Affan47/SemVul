cp(){
    std::ofstream s;

    if ( tDirectories::Var().Open(s, "players.txt") ){
        if (se_PlayerNetIDs.Len()>0)
            s << tColoredString::RemoveColors(ePlayerNetID::Ranking( -1, false ));
        else{
            tOutput o;

            int count=0;
            for(int i=MAXCLIENTS;i>0;i--)
                if (sn_Connections[i].socket)
                    count++;
            if (count==0)
                o << "$online_activity_nobody";
            else if (count==1)
                o << "$online_activity_onespec";
            else
            {
                o.SetTemplateParameter(1, count);
                o << "$online_activity_manyspec";
            }
            o << "\n";
            s << o;
        }
    }
}
