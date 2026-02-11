afm_write(AFFILE *af, unsigned char *buf, uint64_t pos,size_t count)
{
    struct afm_private *ap = AFM_PRIVATE(af);
    if(ap->sr_initialized==0 && afm_split_raw_setup(af)) return -1;
    af_set_callback(ap->sr,af->w_callback);
    int r = (*ap->sr->v->write)(ap->sr,buf,pos,count);
    if(ap->sr->image_size > af->image_size){
	af->image_size      = ap->sr->image_size;
	ap->aff->image_size = ap->sr->image_size;
    }
    return r;
}
