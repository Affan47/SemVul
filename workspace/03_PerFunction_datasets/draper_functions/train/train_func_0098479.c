alc_strtophtrs(s_name,p_layer,lp_l,lp_w)
    char *s_name, *p_layer;
    long *lp_l, *lp_w;
{
    static char *p_l,*p_w,
                 buffer[MBKSZNAME];
            int  i;

#ifdef  JP_DEBUG
    puts( "- Execution de \`alc_strtophtrs\` .");
#endif

    strcpy( buffer, s_name);

    if (  (buffer[0]!='T')||(buffer[2]!='_') ) return FALSE;
    switch( buffer[1] )    {
        case 'N' : *p_layer = NTRANS; break;
        case 'P' : *p_layer = PTRANS; break;
        default  : return FALSE;
        }
    p_l = buffer+3;

    if ( (p_w=strchr(p_l,'_'))==NULL ) return FALSE;
    *(p_w++) = '\0';

    for( i=0; p_l[i]!='\0'; i++)
        if ( !mc_isdigit(p_l[i]) )
            return( FALSE);
    for( i=0; p_w[i]!='\0'; i++)
        if ( !mc_isdigit(p_w[i]) )
            return( FALSE);

    *lp_l = atol( p_l);
    *lp_w = atol( p_w);

    return TRUE;
}
