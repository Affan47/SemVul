set_entity(int x, int y, struct entity *etmp)
{
    if ((x == u.ux) && (y == u.uy))
    {
        u_to_e(etmp);
    }
    else if (MON_AT(x, y))
    {
        m_to_e(m_at(x, y), x, y, etmp);
    }
    else
    {
        etmp->edata = (struct permonst *)0;
    }
}
