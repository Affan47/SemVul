checkitemspawns(int diff)
{
    if(!diff) return;
    loopv(sents) if(sents[i].spawntime)
    {
        sents[i].spawntime -= diff;
        if(sents[i].spawntime<=0)
        {
            sents[i].spawntime = 0;
            sents[i].spawned = true;
            sendf(-1, 1, "ri2", SV_ITEMSPAWN, i);
        }
    }
}
