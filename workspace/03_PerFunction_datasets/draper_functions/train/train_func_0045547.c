treeGetCh ()

{
    int  ch;

    while ((ch = getc(INFILE)) != EOF) {
        if (white(ch)) ;
        else if (ch == '[') {
            if ((ch = treeFinishCom()) == EOF)  break;
        }
        else  break;
    }

    return  ch;
}
