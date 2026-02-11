writehex(unsigned int inp){
        short x;
        unsigned int temp;
        char output[8];
        for (x=6;x>-1;x--){
                temp = inp / doexpon(16,x);
                inp -= temp * doexpon(16,x);
                output[6-x] = convertnumtochar(temp);
        }
        output[7] = convertnumtochar(inp);
        output[8] = 0;
        write(output);
}
