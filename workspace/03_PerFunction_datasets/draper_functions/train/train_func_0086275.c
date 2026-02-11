ForEachHostInFamily(family, func, closure)
int family;
Bool(*func) ();
pointer closure;
{
    HOST *host;

    for (host = validhosts; host; host = host->next)
        if (family == host->family && func(host->addr, host->len, closure))
            return TRUE;
    return FALSE;
}
