dsgw_build_urlprefix_ext(int unescaped)
{
    char	*prefix = dsgw_getvp( DSGW_CGINUM_DOSEARCH );
    char	*urlprefix;

    if (unescaped) {
	urlprefix = PR_smprintf("%s?context=%s&dn=", prefix, context);
    } else {
	urlprefix = PR_smprintf("%s?context=%s&amp;dn=", prefix, context);
    }
    return( urlprefix );
}
