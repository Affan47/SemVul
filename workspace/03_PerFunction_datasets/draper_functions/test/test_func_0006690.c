QIOread(qp)
    QIOSTATE	*qp;
{
    register char	*p;
    register char	*q;
    char		*save;
    int			i;

    while (TRUE) {


        if (qp->End > qp->Start) {


            p = memchr((POINTER)qp->Start,'\n',(SIZE_T)(qp->End - qp->Start));
            if (p != NULL) {
                *p = '\0';
                qp->Length = p - qp->Start;
                save = qp->Start;
                qp->Start = p + 1;
                qp->flag = QIO_ok;
                return save;
            }


            for (p = qp->Buffer, q = qp->Start; q < qp->End; )
                *p++ = *q++;
        }
        else
            p = qp->Buffer;


        i = read(qp->fd, p, (SIZE_T)(&qp->Buffer[qp->Size] - p));
        if (i < 0) {
            qp->flag = QIO_error;
            return NULL;
        }
        if (i == 0) {
            qp->flag = QIO_ok;
            return NULL;
        }
        qp->Count += i;
        qp->Start = qp->Buffer;
        qp->End = &p[i];


        p = memchr((POINTER)qp->Start, '\n', (SIZE_T)(qp->End - qp->Start));
        if (p != NULL) {
            *p = '\0';
            qp->Length = p - qp->Start;
            save = qp->Start;
            qp->Start = p + 1;
            qp->flag = QIO_ok;
            return save;
        }

        if ((qp->End - qp->Start) >= qp->Size) {

            qp->flag = QIO_long;
            qp->Start = qp->End;
            return NULL;
        }


    }
}
