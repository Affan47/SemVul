wrdmwrshift(register word32 *wp, register int32 kwrds,
 register int32 lwlen)
{
 register int32 wi;

 for (wi = kwrds; wi < lwlen; wi++)  wp[wi - kwrds] = wp[wi];
 for (wi = lwlen - kwrds; wi < lwlen; wi++) wp[wi] = 0L;
}
