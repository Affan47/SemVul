find_resource(const void *story_file, int32 story_len,
                         const char *resname, resinfo *info)
{

    if (story_file == 0)
        return FALSE;


    if (tads_match_sig(story_file, story_len, T2_SIGNATURE))
    {
        info->tads_version = 2;
        return t2_find_res(story_file, story_len, resname, info);
    }


    if (tads_match_sig(story_file, story_len, T3_SIGNATURE))
    {
        info->tads_version = 3;
        return t3_find_res(story_file, story_len, resname, info);
    }


    return FALSE;
}
