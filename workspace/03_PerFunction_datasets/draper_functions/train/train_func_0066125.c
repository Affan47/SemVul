fix_last_offset(FILE * fp, int32_t off)
{
    int32_t net;

    if (!STORING_PTRS)
    {
	net = htonl(off);
	fseek(fp, -(sizeof net), SEEK_CUR);
	fwrite(&net, 1, sizeof net, fp);
    }
    else
	Seekpts[Num_pts - 1] = off;
}
