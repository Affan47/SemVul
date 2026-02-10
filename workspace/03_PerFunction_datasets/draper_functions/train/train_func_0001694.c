GetNextUnload()
{

    if (lastLoad != None)
        throw 1;


    trpgManagedTile *tile = NULL;
    for (int i=pageInfo.size()-1;i>=0;i--) {
        LodPageInfo &info = pageInfo[i];
        if ((tile = info.GetNextUnload()))
            break;
    }


    if (tile) {
        lastLoad = Unload;
        lastTile = tile;
        lastLod = tile->location.lod;
    }

    return tile;
}
