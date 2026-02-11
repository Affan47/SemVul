load_sound_resource(glui32 snd, long *len, char **buf)
{
    if (!giblorb_is_resource_map())
    {
        FILE *file;
        char name[1024];

        sprintf(name, "%s/SND%ld", gli_workdir, (long) snd);

        file = fopen(name, "rb");
        if (!file)
            return 0;

        fseek(file, 0, SEEK_END);
        *len = ftell(file);

        *buf = malloc(*len);
        if (!*buf)
        {
            fclose(file);
            return 0;
        }

        fseek(file, 0, 0);
        if (fread(*buf, 1, *len, file) != *len && !feof(file)) return 0;
        fclose(file);


        if (*len > 4 && !memcmp(*buf, "FORM", 4))
            return giblorb_ID_FORM;


        if (*len > 4 && !memcmp(*buf, "WAVE", 4))
            return giblorb_ID_WAVE;


        if (*len > 0x30 && !memcmp(*buf + 0x2c, "SCRM", 4))
            return giblorb_ID_MOD;


        if (*len > 20 && !memcmp(*buf, "Extended Module: ", 17))
            return giblorb_ID_MOD;


        if (*len > 1084)
        {
            char resname[4];
            memcpy(resname, (*buf) + 1080, 4);
            if (!strcmp(resname+1, "CHN") ||
                    !strcmp(resname+2, "CN") ||
                    !strcmp(resname, "M.K.") || !strcmp(resname, "M!K!") ||
                    !strcmp(resname, "FLT4") || !strcmp(resname, "CD81") ||
                    !strcmp(resname, "OKTA") || !strcmp(resname, "    "))
                return giblorb_ID_MOD;
        }


        if (*len > 4 && !memcmp(*buf, "OggS", 4))
            return giblorb_ID_OGG;


        if (*len > 2 && !memcmp(*buf, "\377\372", 2))
            return giblorb_ID_MP3;

        return giblorb_ID_MP3;
    }
    else
    {
        FILE *file;
        glui32 type;
        long pos;

        giblorb_get_resource(giblorb_ID_Snd, snd, &file, &pos, len, &type);
        if (!file)
            return 0;

        *buf = malloc(*len);
        if (!*buf)
            return 0;

        fseek(file, pos, 0);
        if (fread(*buf, 1, *len, file) != *len && !feof(file)) return 0;
        return type;
    }
}
