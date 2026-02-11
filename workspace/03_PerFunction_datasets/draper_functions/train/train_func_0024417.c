flagmessage(int flag, int message, int actor, int cn = -1)
{
    if(message == FM_KTFSCORE)
        sendf(cn, 1, "riiiii", SV_FLAGMSG, flag, message, actor, (gamemillis - sflaginfos[flag].stolentime) / 1000);
    else
        sendf(cn, 1, "riiii", SV_FLAGMSG, flag, message, actor);
}
