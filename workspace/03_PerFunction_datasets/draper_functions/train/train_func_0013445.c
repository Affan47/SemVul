mapsigntype(nbbuf_T *buf, int localsigntype)
{
    if (--localsigntype >= 0 && localsigntype < buf->signmapused)
	return buf->signmap[localsigntype];

    return 0;
}
