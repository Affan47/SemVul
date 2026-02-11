afd_add_file(AFFILE *af,const char *fname_)
{
    struct afd_private *ap = AFD_PRIVATE(af);
    const char *segs_to_copy[] = {AF_BADFLAG,
				  AF_CASE_NUM,
				  AF_IMAGE_GID,
				  AF_ACQUISITION_ISO_COUNTRY,
				  AF_ACQUISITION_COMMAND_LINE,
				  AF_ACQUISITION_DATE,
				  AF_ACQUISITION_NOTES,
				  AF_ACQUISITION_DEVICE,
				  AF_ACQUISITION_TECHNICIAN,
				  AF_DEVICE_MANUFACTURER,
				  AF_DEVICE_MODEL,
				  AF_DEVICE_SN,
				  AF_DEVICE_FIRMWARE,
				  AF_DEVICE_SOURCE,
				  AF_CYLINDERS,
				  AF_HEADS,
				  AF_SECTORS_PER_TRACK,
				  AF_LBA_SIZE,
				  AF_HPA_PRESENT,
				  AF_DCO_PRESENT,
				  AF_LOCATION_IN_COMPUTER,
				  AF_DEVICE_CAPABILITIES,
				  0};

    char fname[MAXPATHLEN+1];
    memset(fname,0,sizeof(fname));
    if(fname_){
	strlcpy(fname,fname_,sizeof(fname));
    }
    else {
	aff_filename(af,fname,sizeof(fname),ap->num_afs);
    }

    int new_file = access(fname,F_OK)!=0;

    AFFILE *af2 = af_open(fname,af->openflags|AF_NO_CRYPTO,af->openmode);
    if(af2==0){
	(*af->error_reporter)("open(%s,%d,%d) failed: %s\n",
			      fname,af->openflags,af->openmode,strerror(errno));
	return -1;
    }

    ap->num_afs += 1;
    ap->afs = (AFFILE **)realloc(ap->afs,sizeof(AFFILE *) * ap->num_afs);
    ap->afs[ap->num_afs-1] = af2;

    if(new_file){

	af_enable_compression(af2,af->compression_type,af->compression_level);
	af_set_pagesize(af2,af->image_pagesize);
	af_set_sectorsize(af2,af->image_sectorsize);
	af_update_seg(af,AF_AFF_FILE_TYPE,0,(const u_char *)"AFD",3);


	if(ap->num_afs>1){
	    AFFILE *af0 = ap->afs[0];
	    memcpy(af2->badflag,af0->badflag,af->image_sectorsize);
	    af2->bytes_memcpy += af->image_sectorsize;

	    for(const char **segname=segs_to_copy;*segname;segname++){
		unsigned char data[65536];
		size_t datalen = sizeof(data);
		unsigned long arg=0;

		if(af_get_seg(af0,*segname,&arg,data,&datalen)==0){
		    int r = af_update_seg(af2,*segname,arg,data,datalen);
		    if(r!=0){
			(*af->error_reporter)("afd_add_file: could not update %s in %s (r=%d)",
					      *segname,af_filename(af2),r);
		    }
		}
	    }
	}
    }

    return 0;
}
