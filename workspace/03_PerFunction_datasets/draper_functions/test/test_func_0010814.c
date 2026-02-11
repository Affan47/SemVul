lk_playlist_insert(playlist * pl, unsigned int at, uint32_t fid,
                       uint32_t fid_generation)
{
    at=at*8;
    if(at+4<pl->length){
        pl->length+=8;
        pl->playlist=(char *)realloc(pl->playlist, pl->length);
        memmove(&pl->playlist[12+at], &pl->playlist[4+at], pl->length-at-12);
        return lk_playlist_set_item(pl, at/8, fid, fid_generation);
    }else return lk_playlist_append(pl, fid, fid_generation);
}
