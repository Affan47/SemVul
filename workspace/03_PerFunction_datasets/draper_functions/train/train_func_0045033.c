lk_playlist_read(char * name)
{
    playlist *pl;

    pl=malloc(sizeof(playlist));
    if(pl){
        pl->fid=get_playlist_fid(name);
        if(pl->fid!=0){
            if(lk_properties_get_property(pl->fid, "playlist")){
                pl->length=lk_playlist_unescape(
                    lk_properties_get_property(pl->fid, "playlist"),
                    &pl->playlist);
                pl->name=strdup(name);
            }else{
                free(pl);
                pl=lk_playlist_create(name);
                pl->fid=get_playlist_fid(name);
            }
            return pl;
        }else{
            free(pl);
            return NULL;
        }
    }else return NULL;
}
