_parse_accessible_playlists(JNIEnv* env, BITBUFFER* buf)
{

    bb_seek(buf, 32, SEEK_CUR);

    int count = bb_read(buf, 11);
    jobjectArray playlists = bdj_make_array(env, "java/lang/String", count);

    jboolean access_to_all_flag = bb_read(buf, 1);
    jboolean autostart_first_playlist = bb_read(buf, 1);


    bb_seek(buf, 19, SEEK_CUR);

    for (int i = 0; i < count; i++) {
        char playlist_name[6];
        _get_string(buf, playlist_name, 5);
        jstring jplaylist_name = (*env)->NewStringUTF(env, playlist_name);
        JNICHK(jplaylist_name);

        (*env)->SetObjectArrayElement(env, playlists, i, jplaylist_name);


        bb_seek(buf, 8, SEEK_CUR);
    }

    return bdj_make_object(env, "org/videolan/bdjo/PlayListTable", "(ZZ[Ljava/lang/String;)V",
            access_to_all_flag, autostart_first_playlist, playlists);
}
