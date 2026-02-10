addbuf(WImage *w, uchar *buf, int nbuf)
{
        int n;
        if(buf == nil || w->outp+nbuf > w->eout) {
                if(w->loutp==w->outbuf){
                        eprintf("buffer too small for line\n");
                        return ERROR;
                }
                n=w->loutp-w->outbuf;
                fprintf(w->f, "%11d %11d ", w->r.max.y, n);
                fwrite(w->outbuf, 1, n, w->f);
                w->r.min.y=w->r.max.y;
                w->outp=w->outbuf;
                w->loutp=w->outbuf;
                zerohash(w);
                return -1;
        }

        memmove(w->outp, buf, nbuf);
        w->outp += nbuf;
        return nbuf;
}
