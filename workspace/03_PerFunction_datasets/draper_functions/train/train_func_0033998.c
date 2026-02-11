lame_decode_fromfile(FILE * fd, short pcm_l[], short pcm_r[], mp3data_struct * mp3data)
{
    int     ret = 0;
    size_t  len = 0;
    unsigned char buf[1024];


    ret = hip_decode1_headers(global.hip, buf, len, pcm_l, pcm_r, mp3data);
    if (ret != 0)
        return ret;


    while (1) {
        len = fread(buf, 1, 1024, fd);
        if (len == 0) {

            ret = hip_decode1_headers(global.hip, buf, len, pcm_l, pcm_r, mp3data);
            if (ret <= 0) {
                hip_decode_exit(global.hip);
                global.hip = 0;
                return -1;
            }
            break;
        }

        ret = hip_decode1_headers(global.hip, buf, len, pcm_l, pcm_r, mp3data);
        if (ret == -1) {
            hip_decode_exit(global.hip);
            global.hip = 0;
            return -1;
        }
        if (ret > 0)
            break;
    }
    return ret;
}
