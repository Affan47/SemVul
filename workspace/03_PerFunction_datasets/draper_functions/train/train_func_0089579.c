setftty(void)
{
register int ef = 0;
#ifdef LINT
register int cf = 0;
#else
register int cf = CBRKON(CBRKMASK);
#endif
register int change = 0;
	iflags.cbreak = ON;
	iflags.echo = OFF;

	if((curttyb.echoflgs & ECHO) != ef){
		curttyb.echoflgs &= ~ECHO;

		change++;
	}
	if((curttyb.cbrkflgs & CBRKMASK) != cf){
		curttyb.cbrkflgs &= ~CBRKMASK;
		curttyb.cbrkflgs |= cf;
#ifdef USG

		curttyb.c_cc[VMIN] = 1;
		curttyb.c_cc[VTIME] = 0;
# ifdef POSIX_JOB_CONTROL


#  ifdef VSUSP
		curttyb.c_cc[VSUSP] = nonesuch;
#  else
		curttyb.c_cc[VSWTCH] = nonesuch;
#  endif
# endif
# ifdef VDSUSP
		curttyb.c_cc[VDSUSP] = nonesuch;
# endif
# ifdef VREPRINT
		curttyb.c_cc[VREPRINT] = nonesuch;
# endif
# ifdef VDISCARD
		curttyb.c_cc[VDISCARD] = nonesuch;
# endif
# ifdef VWERASE
		curttyb.c_cc[VWERASE] = nonesuch;
# endif
# ifdef VLNEXT
		curttyb.c_cc[VLNEXT] = nonesuch;
# endif
#endif
		change++;
	}
	if(!IS_7BIT(inittyb)) curttyb.inputflags &=~ STRIPHI;


	if(intr_char != nonesuch && curttyb2.intr_sym != '\003') {
	    curttyb2.intr_sym = '\003';
	    change++;
	}

	if(change) setctty();
	start_screen();
}
