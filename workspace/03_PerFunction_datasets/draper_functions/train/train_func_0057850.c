srom_data(u_int command, u_long addr)
{
    int i;
    short word = 0;
    s32 tmp;

    for (i=0; i<16; i++) {
	sendto_srom(command  | DT_CLK, addr);
	tmp = getfrom_srom(addr);
	sendto_srom(command, addr);

	word = (word << 1) | ((tmp >> 3) & 0x01);
    }

    sendto_srom(command & 0x0000ff00, addr);

    return word;
}
