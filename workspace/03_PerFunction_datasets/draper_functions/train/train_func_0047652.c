dev_set_kernel_args(char* arglist){
    FILE *argfile;
    int count;

    DEBUG("DEVICE: dev_set_kernel_args\n");

    argfile = fopen("kernelargs","w+");
    if(argfile == NULL)
        return -1;
    count = fprintf(argfile,"%s",arglist);
    fclose(argfile);
    if(count < 0)
        return -1;

    return 0;
}
