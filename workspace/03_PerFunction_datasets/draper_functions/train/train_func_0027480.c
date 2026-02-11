psf_seek(u32 t)
{
 seektime=t*441/10;
 if(seektime>sampcount) return(1);
 return(0);
}
