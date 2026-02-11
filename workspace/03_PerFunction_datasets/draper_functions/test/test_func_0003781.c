av_generate_path(ventry *ve, char **pathp)
{
    int res;

    if(ve == NULL)
        *pathp = NULL;
    else {
        res = av_generate_path(ve->mnt->base, pathp);
        if(res < 0)
            return res;

        res = add_segment(ve, pathp);
        if(res < 0) {
            av_free(*pathp);
            return res;
        }
    }

    return 0;
}
