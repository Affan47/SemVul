gsd_switchlight(int num, int on)
{
    short defin;

    defin = on ? num : 0;

    if (defin) {
	glEnable(GL_LIGHT0 + num);
    }
    else {
	glDisable(GL_LIGHT0 + num);
    }

    return;
}
