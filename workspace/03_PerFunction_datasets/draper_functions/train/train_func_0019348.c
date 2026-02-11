printMac(char * mac, int macLen) {
    ostringstream tmp;
    int i;
    unsigned char x;

    for (i=0; i<macLen; i++) {
        if (i)
            tmp << ":";
        tmp << hex;
        tmp.fill('0');
        tmp.width(2);
        x = (unsigned char) mac[i];
        tmp << (unsigned int)x;
    }
    return tmp.str();
}
