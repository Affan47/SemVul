debug_ttymode(ttymode_t *ttymode)
{


    fprintf(stderr, "Input flags:  ");
    SHOW_TTY_FLAG(IGNBRK, "IGNBRK");
    SHOW_TTY_FLAG(BRKINT, "BRKINT");
    SHOW_TTY_FLAG(IGNPAR, "IGNPAR");
    SHOW_TTY_FLAG(PARMRK, "PARMRK");
    SHOW_TTY_FLAG(INPCK, "INPCK");
    SHOW_TTY_FLAG(ISTRIP, "ISTRIP");
    SHOW_TTY_FLAG(INLCR, "INLCR");
    SHOW_TTY_FLAG(IGNCR, "IGNCR");
    SHOW_TTY_FLAG(ICRNL, "ICRNL");
    SHOW_TTY_FLAG(IXON, "IXON");
    SHOW_TTY_FLAG(IXOFF, "IXOFF");
#  ifdef IUCLC
    SHOW_TTY_FLAG(IUCLC, "IUCLC");
#  endif
#  ifdef IXANY
    SHOW_TTY_FLAG(IXANY, "IXANY");
#  endif
#  ifdef IMAXBEL
    SHOW_TTY_FLAG(IMAXBEL, "IMAXBEL");
#  endif
    fprintf(stderr, "\n");

    fprintf(stderr, "Control character mappings:  ");
    SHOW_CONT_CHAR(VINTR, "VINTR");
    SHOW_CONT_CHAR(VQUIT, "VQUIT");
    SHOW_CONT_CHAR(VERASE, "VERASE");
    SHOW_CONT_CHAR(VKILL, "VKILL");
    SHOW_CONT_CHAR(VEOF, "VEOF");
    SHOW_CONT_CHAR(VEOL, "VEOL");
#  ifdef VEOL2
    SHOW_CONT_CHAR(VEOL2, "VEOL2");
#  endif
#  ifdef VSWTC
    SHOW_CONT_CHAR(VSWTC, "VSWTC");
#  endif
#  ifdef VSWTCH
    SHOW_CONT_CHAR(VSWTCH, "VSWTCH");
#  endif
    SHOW_CONT_CHAR(VSTART, "VSTART");
    SHOW_CONT_CHAR(VSTOP, "VSTOP");
    SHOW_CONT_CHAR(VSUSP, "VSUSP");
#  ifdef VDSUSP
    SHOW_CONT_CHAR(VDSUSP, "VDSUSP");
#  endif
#  ifdef VREPRINT
    SHOW_CONT_CHAR(VREPRINT, "VREPRINT");
#  endif
#  ifdef VDISCRD
    SHOW_CONT_CHAR(VDISCRD, "VDISCRD");
#  endif
#  ifdef VWERSE
    SHOW_CONT_CHAR(VWERSE, "VWERSE");
#  endif
#  ifdef VLNEXT
    SHOW_CONT_CHAR(VLNEXT, "VLNEXT");
#  endif
    fprintf(stderr, "\n\n");
}
