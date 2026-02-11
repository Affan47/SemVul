Face2Cmd(uint8 *data,  int len)
{
    int pnum;
    uint8 setnum;
    uint32  checksum;
    char *face;


    if (!use_config[CONFIG_CACHE]) {
        LOG(LOG_WARNING,"common::Face2Cmd","Received a 'face' command when we are not caching");
        return;
    }
    pnum = GetShort_String(data);
    setnum = data[2];
    checksum = GetInt_String(data+3);
    face = (char*)data+7;
    data[len] = '\0';

    finish_face_cmd(pnum, checksum, 1, face,setnum);
}
