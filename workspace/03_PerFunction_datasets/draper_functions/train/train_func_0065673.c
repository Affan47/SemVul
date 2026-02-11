gf_seng_create_new_au(GF_StreamContext *sc, u32 time)
{
    GF_AUContext *new_au, *last_au;
    last_au = gf_list_last(sc->AUs);
    if (last_au && last_au->timing == time) {
        GF_LOG(GF_LOG_DEBUG, GF_LOG_SCENE, ("[SceneEngine] Forcing new AU\n"));
        time++;
    }
    new_au = gf_sm_stream_au_new(sc, time, 0, 0);
    return new_au;
}
