af_get_segq(AFFILE *af,const char *name,int64_t *aff_quad)
{
    unsigned char buf[8];
    size_t  bufsize = sizeof(buf);

    if(af_get_seg(af,name,0,(unsigned char *)&buf,&bufsize)){
	return -1;
    }
    if(bufsize!=sizeof(struct aff_quad)){
	return -1;
    }

    *aff_quad = af_decode_q(buf);
    return 0;
}
