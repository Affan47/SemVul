epia_test_proto( PIA *pi, char * scratch, int verbose )

{       int     j, k, f;
	int	e[2] = {0,0};

        epia_connect(pi);
        for (j=0;j<2;j++) {
            WR(6,0xa0+j*0x10);
            for (k=0;k<256;k++) {
                WR(2,k^0xaa);
                WR(3,k^0x55);
                if (RR(2) != (k^0xaa)) e[j]++;
                }
	    WR(2,1); WR(3,1);
            }
        epia_disconnect(pi);

        f = 0;
        epia_connect(pi);
        WR(0x84,8);
        epia_read_block(pi,scratch,512);
        for (k=0;k<256;k++) {
            if ((scratch[2*k] & 0xff) != ((k+1) & 0xff)) f++;
            if ((scratch[2*k+1] & 0xff) != ((-2-k) & 0xff)) f++;
        }
        WR(0x84,0);
        epia_disconnect(pi);

        if (verbose)  {
            printk("%s: epia: port 0x%x, mode %d, test=(%d,%d,%d)\n",
                   pi->device,pi->port,pi->mode,e[0],e[1],f);
        }

        return (e[0] && e[1]) || f;

}
