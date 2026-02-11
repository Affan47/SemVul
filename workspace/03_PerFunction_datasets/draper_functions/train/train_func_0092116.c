iprtoa(const struct iprange &ipr)
{
    static string s[2];
    static int buf = 0;
    buf = (buf + 1) % 2;
    if(ipr.lr == ipr.ur) copystring(s[buf], iptoa(ipr.lr));
    else formatstring(s[buf])("%s-%s", iptoa(ipr.lr), iptoa(ipr.ur));
    return s[buf];
}
