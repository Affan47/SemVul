SendConfig(bool force, int peer){
    if ( (changed || force) && sn_GetNetState()==nSERVER)
    {

        nMessage *m=new nMessage(transferConfig);
        *m << title;
        NetWriteVal(*m);
        if (peer==-1)
        {
            m->BroadCast();
            changed = false;
        }
        else
            m->Send(peer);
    }
}
