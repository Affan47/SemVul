term_init(void)
{
    struct termios tattr;

    if (!(tty=isatty(0)))
    {
        fprintf(stderr,"Warning! isatty() reports stdin is not a terminal.\n");
        return 0;
    }

    tcgetattr(0,&old_tattr);
    tattr=old_tattr;

    tattr.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP
                       |INLCR|IGNCR|ICRNL|IXON);
    tattr.c_oflag &= ~OPOST;
    tattr.c_lflag &= ~(ECHO|ECHONL|ICANON|ISIG|IEXTEN);
    tattr.c_cflag &= ~(CSIZE|PARENB);
    tattr.c_cflag |= CS8;

#ifndef IGNORE_INT
    tattr.c_lflag|=ISIG;
#endif
    tattr.c_cc[VMIN]=1;
    tattr.c_cc[VTIME]=0;
    tcsetattr(0,TCSANOW,&tattr);

    return 1;
}
