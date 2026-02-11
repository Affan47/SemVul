minher32()
{
    minher();
    if (defsize != 0x4)
	oprefix = 0x66;
    needcpu(3);
}
