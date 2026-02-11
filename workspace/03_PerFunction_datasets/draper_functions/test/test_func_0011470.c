scallvotesuc(voteinfo *v)
{
    if(!v->isvalid()) return;
    DELETEP(curvote);
    curvote = v;
    clients[v->owner]->lastvotecall = servmillis;
    clients[v->owner]->nvotes--;
    sendf(v->owner, 1, "ri", SV_CALLVOTESUC);
    logline(ACLOG_INFO, "[%s] client %s called a vote: %s", clients[v->owner]->hostname, clients[v->owner]->name, v->action->desc ? v->action->desc : "[unknown]");
}
