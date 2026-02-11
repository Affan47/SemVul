rfio_HsmIf_open_limbysz(const char *path, int flags, mode_t mode, u_signed64 maxsize, int mode64) {
    int rc = -1;
    int save_serrno;
#if defined(CNS_ROOT)
    struct Cns_filestat st;
    stage_hsm_t *hsmfile = NULL;
#endif

#if defined(CNS_ROOT)
    if ( rfio_HsmIf_IsCnsFile(path) ) {


        memset(&st,'\0',sizeof(st));
        rc = Cns_stat(path,&st);


        if ( rc == -1 || ((flags & O_TRUNC) != 0)) st.filesize = 0;


        hsmfile = (stage_hsm_t *)calloc(1,sizeof(stage_hsm_t));
        {
          char *p;
          char *pfn;
          char *turl;

	  hsmfile->sfn = strdup(path);
	  hsmfile->r_token = malloc(CA_MAXDPMTOKENLEN+1);
          TRACE(3,"rfio","Calling dpm_getturl with: %s %x\n", path, flags);
          if ((turl = dpm_getturl(path, flags, maxsize, hsmfile->r_token)) == NULL) {
            (void)CnsCleanup(&hsmfile);
            return (-1);
	  }
	  pfn = turl + 7;
	  p = strchr (pfn, '/');
	  *p = ':';
          if (mode64) {
            rc = rfio_open64(pfn, flags, mode);
          } else {
            rc = rfio_open(pfn, flags, mode);
          }
	  free(turl);
	  if (rc  == -1) {
            (void)CnsCleanup(&hsmfile);
            return (-1);
	  }
        }
        if ( AddCnsFileDescriptor(rc,flags,hsmfile) == -1 ) {
            save_serrno = serrno;
            (void)CnsCleanup(&hsmfile);
            rfio_close(rc);
            serrno = save_serrno;
            return(-1);
        }
        if ( st.filesize == 0 ) SetCnsWrittenTo(rc);
    }
#endif
    return(rc);
}
