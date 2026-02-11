is_arp(void *wh, int len)
{
        int arpsize = 8 + 8 + 10*2;

        if(wh) {}


        if (len == arpsize || len == 54)
            return 1;

        return 0;
}
