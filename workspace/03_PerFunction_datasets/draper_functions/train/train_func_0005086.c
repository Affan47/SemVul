eatmdone(void)
{

    if (eatmbuf)
    {
        if (nomovemsg == eatmbuf) nomovemsg = 0;
        free(eatmbuf),  eatmbuf = 0;
    }

    if (youmonst.m_ap_type)
    {
        youmonst.m_ap_type = M_AP_NOTHING;
        newsym(u.ux,u.uy);
    }
    return 0;
}
