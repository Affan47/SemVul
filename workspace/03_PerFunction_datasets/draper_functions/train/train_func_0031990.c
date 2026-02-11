GSFcn1(int x) {
        int timeout=TMOUT;
        unsigned char result;

        while (timeout) {

                result<<=4;
                result|=SendNibble(x);


                if (result==0x67) break;

                SendNibble(x);
                SendNibble(x>>4);

                timeout--;
        }

        if (!timeout) return 1;
        return 0;
}
