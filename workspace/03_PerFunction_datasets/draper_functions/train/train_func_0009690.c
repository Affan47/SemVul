any_overlap(char *s1, char *s2)
{   int a, b, i, j, flag;
    a=strlen(s1); b=strlen(s2);
    for (i=1-b; i<a; i++)
    {   flag=0;
        for (j=0; j<b; j++)
            if ((0<=i+j)&&(i+j<=a-1))
                if (s1[i+j]!=s2[j]) flag=1;
        if (flag==0) return(1);
    }
    return(0);
}
