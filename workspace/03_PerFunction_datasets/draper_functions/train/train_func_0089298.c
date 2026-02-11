qwrite(char *file, char buffer[], int n){


     if (noutchar + n > noutmax) return(0);

     memcpy(&file[noutchar], buffer, n);
     noutchar += n;

     return(n);
}
