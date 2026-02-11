generate_transmitted_iv(char *transmitted_iv){
        FILE *fp;
        int x;
        int seed=0;


        fp=fopen("/dev/urandom","r");
        if(fp!=NULL){
                seed=fgetc(fp);
                fclose(fp);
                }


        else
                seed=(int)time(NULL);


        srand(seed);
        for(x=0;x<TRANSMITTED_IV_SIZE;x++)
                transmitted_iv[x]=(int)((256.0*rand())/(RAND_MAX+1.0));

        return;
        }
