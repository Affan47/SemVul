substring_command(char *arg,struct session *ses)
{
    char left[BUFFER_SIZE], mid[BUFFER_SIZE], right[BUFFER_SIZE], *p;
    WC buf[BUFFER_SIZE],*lptr,*rptr;
    int l,r,s,w;

    arg = get_arg(arg, left, 0, ses);
    arg = get_arg(arg, mid, 0, ses);
    arg = get_arg(arg, right, 1, ses);
    l=strtol(mid,&p,10);
    if (*p==',')
        r=strtol(p+1,&p,10);
    else
        r=l;
    if (l<1)
        l=1;

    if (!*left || (p==mid) || (*p) || (r<0))
        tintin_eprintf(ses, "#SYNTAX: substr <var> <l>[,<r>] <string>");
    else
    {
        p=mid;
        TO_WC(buf, right);
        lptr=buf;
        s=1;
        while(*lptr)
        {
            w=wcwidth(*lptr);
            if (w<0)
                w=0;
            if (w && s>=l)
                break;
            lptr++;
            s+=w;
        }
        if (s>l)
            *p++=' ';
        rptr=lptr;
        while(w=wcwidth(*rptr), *rptr)
        {
            if (w<0)
                w=0;
            if (w && s+w>r+1)
                break;
            rptr++;
            s+=w;
        }
        if (rptr>lptr)
            p+=wc_to_utf8(p, lptr, rptr-lptr, BUFFER_SIZE-3);
        if (s==r && w==2)
            *p++=' ';
        *p=0;
        set_variable(left,mid,ses);
    }
}
