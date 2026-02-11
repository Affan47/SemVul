svote(int sender, int vote, ENetPacket *msg)
{
    if(!curvote || !valid_client(sender) || vote < VOTE_YES || vote > VOTE_NO) return false;
    if(clients[sender]->vote != VOTE_NEUTRAL)
    {
        sendf(sender, 1, "ri2", SV_CALLVOTEERR, VOTEE_MUL);
        return false;
    }
    else
    {
        sendpacket(-1, 1, msg, sender);

        clients[sender]->vote = vote;
        logline(ACLOG_DEBUG,"[%s] client %s voted %s", clients[sender]->hostname, clients[sender]->name, vote == VOTE_NO ? "no" : "yes");
        curvote->evaluate();
        return true;
    }
}
