convert_mac2hex(UINT8 *hw_addr,INTN l, CHAR16 *str)
{
 	UINTN i;

	for (i=0 ; i < l; i++) {
		str[3*i] = hexa[(hw_addr[i] & 0xf0)>>4];
		str[3*i+1] = hexa[hw_addr[i] & 0x0f];
		str[3*i+2] = ':';
	}
	str[3*l-1]='\0';
}
