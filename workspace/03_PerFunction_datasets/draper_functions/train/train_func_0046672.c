PartialBlock(u64 msglen,u32* rkey_enc,u64 j,
              const unsigned char *inb,unsigned char *outb,
			  int flag,bst128 initcounter,bst128 counter){
	u8 i;
	bst128 sin,sout;

    sin.s[0]=sin.s[1]=msglen;

	SilverEncrypt(sin.t,sout.t,rkey_enc,counter.t);

	i=0;
	if(flag){
		while(j<msglen){
			outb[j]=inb[j]^sout.b[i];
			sout.b[i]^=outb[j];


			j++;i++;
		}
	}
	else {
		while(j<msglen){
			sout.b[i]=outb[j]=inb[j]^sout.b[i];
			j++;i++;
		}
	}
	sout.b[15]=i;

	NADD64(counter,initcounter,counter);
	SilverEncrypt(sout.t,sin.t,rkey_enc,counter.t);
return sin;
 }
