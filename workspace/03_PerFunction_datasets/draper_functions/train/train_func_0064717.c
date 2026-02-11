ARTopenbyid(msg_id, ap)
    char	*msg_id;
    ARTNUM	*ap;
{
    QIOSTATE	*qp;
    char	*p;
    char	*q;

    *ap = 0;
    if ((p = HISgetent(msg_id, FALSE)) == NULL)
	return NULL;
    if ((qp = QIOopen(p, QIO_BUFFER)) == NULL)
	return NULL;
    CloseOnExec(QIOfileno(qp), TRUE);
    p += strlen(_PATH_SPOOL) + 1;
    if ((q = strrchr(p, '/')) != NULL)
	*q++ = '\0';
    if (GRPlast[0] && EQ(p, GRPlast))
	*ap = atol(q);
    return qp;
}
