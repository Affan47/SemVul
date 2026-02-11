fstReaderOpen(const char *nam)
{
struct fstReaderContext *xc = calloc(1, sizeof(struct fstReaderContext));

if((!nam)||(!(xc->f=fopen(nam, "rb"))))
        {
        free(xc);
        xc=NULL;
        }
        else
        {
        int flen = strlen(nam);
        char *hf = calloc(1, flen + 6);
	int rc;

#if defined(__MINGW32__) || defined(FST_MACOSX)
	setvbuf(xc->f, (char *)NULL, _IONBF, 0);
#endif

        memcpy(hf, nam, flen);
        strcpy(hf + flen, ".hier");
        xc->fh = fopen(hf, "rb");

	free(hf);
	xc->filename = strdup(nam);
	rc = fstReaderInit(xc);

	if((rc) && (xc->vc_section_count) && (xc->maxhandle) && ((xc->fh)||(xc->contains_hier_section)))
		{

		xc->do_rewind = 1;
		}
		else
		{
		fstReaderClose(xc);
		xc = NULL;
		}
	}

return(xc);
}
