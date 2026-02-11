memspeed(ulong src, ulong len, int iter)
{
	int i;
	ulong dst, wlen;
	ulong st_low, st_high;
	ulong end_low, end_high;
	ulong cal_low, cal_high;

	if (cpu_id.fid.bits.rdtsc == 0 ) {
		return(-1);
	}
	if (len == 0) return(-2);

	dst = src + len;
	wlen = len / 4;


	asm __volatile__ ("rdtsc":"=a" (st_low),"=d" (st_high));
	for (i=0; i<iter; i++) {
		asm __volatile__ (
			"movl %0,%%esi\n\t" \
 		 	"movl %1,%%edi\n\t" \
 		 	"movl %2,%%ecx\n\t" \
 		 	"cld\n\t" \
 		 	"rep\n\t" \
 		 	"movsl\n\t" \
			:: "g" (src), "g" (dst), "g" (0)
			: "esi", "edi", "ecx"
		);
	}
	asm __volatile__ ("rdtsc":"=a" (cal_low),"=d" (cal_high));


	asm __volatile__ (
		"subl %2,%0\n\t"
		"sbbl %3,%1"
		:"=a" (cal_low), "=d" (cal_high)
		:"g" (st_low), "g" (st_high),
		"0" (cal_low), "1" (cal_high)
	);


	asm __volatile__ (
		"movl %0,%%esi\n\t" \
		"movl %1,%%edi\n\t" \
 	 	"movl %2,%%ecx\n\t" \
 	 	"cld\n\t" \
 	 	"rep\n\t" \
 	 	"movsl\n\t" \
		:: "g" (src), "g" (dst), "g" (wlen)
		: "esi", "edi", "ecx"
	);
	asm __volatile__ ("rdtsc":"=a" (st_low),"=d" (st_high));
	for (i=0; i<iter; i++) {
	        asm __volatile__ (
			"movl %0,%%esi\n\t" \
			"movl %1,%%edi\n\t" \
 		 	"movl %2,%%ecx\n\t" \
 		 	"cld\n\t" \
 		 	"rep\n\t" \
 		 	"movsl\n\t" \
			:: "g" (src), "g" (dst), "g" (wlen)
			: "esi", "edi", "ecx"
		);
	}
	asm __volatile__ ("rdtsc":"=a" (end_low),"=d" (end_high));


	asm __volatile__ (
		"subl %2,%0\n\t"
		"sbbl %3,%1"
		:"=a" (end_low), "=d" (end_high)
		:"g" (st_low), "g" (st_high),
		"0" (end_low), "1" (end_high)
	);

	asm __volatile__ (
		"subl %2,%0\n\t"
		"sbbl %3,%1"
		:"=a" (end_low), "=d" (end_high)
		:"g" (cal_low), "g" (cal_high),
		"0" (end_low), "1" (end_high)
	);


	if (end_high) {
		return(-3);
	}
	end_low /= 2;


	end_low /= len;
	end_low *= 1024;
	end_low /= iter;
	if (end_low == 0) {
		return(-4);
	}


	if (tsc_invariable) end_low = correct_tsc(end_low);

	return((v->clks_msec)/end_low);
}
