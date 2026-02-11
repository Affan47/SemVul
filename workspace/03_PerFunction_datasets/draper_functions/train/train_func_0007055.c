initcon()
{
    struct termios new;

    if (!ioset) {
	tcgetattr(0, &old);

        Erasechar = old.c_cc[VERASE];
        eraseline = old.c_cc[VKILL];

        new = old;

	new.c_iflag &= ~(IXON|IXOFF|IXANY|ICRNL|INLCR);
	new.c_lflag &= ~(ICANON|ISIG|ECHO);
	new.c_oflag = 0;

	tcsetattr(0, TCSANOW, &new);
        ioset=1;
    }
}
