print_sector(AFFILE *af,unsigned char *buf)
{
    for(unsigned int i=0;i<af->image_sectorsize;i++){
	if(isprint(buf[i])){
	    putchar(buf[i]);
	}
	else {
	    putchar('.');
	}
	if(i%64==63) putchar('\n');
    }
}
