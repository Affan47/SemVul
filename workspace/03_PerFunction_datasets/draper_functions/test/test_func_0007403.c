errorfn(struct arg_file *parent, FILE *fp, int errorcode, const char *argval, const char *progname)
    {
    const char *shortopts = parent->hdr.shortopts;
    const char *longopts  = parent->hdr.longopts;
    const char *datatype  = parent->hdr.datatype;


    argval = argval ? argval : "";

    fprintf(fp,"%s: ",progname);
    switch(errorcode)
        {
        case EMINCOUNT:
            fputs("missing option ",fp);
            arg_print_option(fp,shortopts,longopts,datatype,"\n");
            break;

        case EMAXCOUNT:
            fputs("excess option ",fp);
            arg_print_option(fp,shortopts,longopts,argval,"\n");
            break;

        default:
            fprintf(fp,"unknown error at \"%s\"\n",argval);
        }
    }
