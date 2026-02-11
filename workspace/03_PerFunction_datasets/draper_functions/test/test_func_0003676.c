match_nickname(const void *k, void *v, void *a)
{
    PRStatus nssrv;
    NSSCertificate *c;
    NSSUTF8 *nickname;
    nssList *subjectList = (nssList *)v;
    struct nickname_template_str *nt = (struct nickname_template_str *)a;
    nssrv = nssList_GetArray(subjectList, (void **)&c, 1);
    nickname = nssCertificate_GetNickname(c, NULL);
    if (nssrv == PR_SUCCESS && nickname &&
         nssUTF8_Equal(nickname, nt->nickname, &nssrv))
    {
	nt->subjectList = subjectList;
    }
    nss_ZFreeIf(nickname);
}
