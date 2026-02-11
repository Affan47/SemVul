mii_read(int phy_id, int location)
{
    int i;

    outl((phy_id << 9) | (location << 4) | MII_READOP, mmctl);


    for (i = 4000; i > 0; i--)
	if ((inl(mmctl) & MII_READOP) == 0)
	    break;
    return inw(mmdata);
}
