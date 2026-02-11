getC32(data, order)
char *data;
int order;
{
    unsigned char *p = (unsigned char *)data;
    unsigned long x;

    if (order == ORDER_BIG) {
	x = (p[0]<<24) | (p[1]<<16) | (p[2]<<8) | p[3];
    } else {
	x = p[0] | (p[1]<<8) | (p[2]<<16) | (p[3]<<24);
    }
    return x;
}
