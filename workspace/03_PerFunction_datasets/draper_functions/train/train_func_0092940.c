NewSpawnPoint(const eCoord &loc,const eCoord &dir){
    gSpawnPoint *s=tNEW(gSpawnPoint) (loc,dir);
    spawnPoints.Add(s,s->id);
}
