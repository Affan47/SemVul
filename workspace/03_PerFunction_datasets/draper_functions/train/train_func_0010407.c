Log_queue(LogObject *self, const char *msg, int len)
{
    const char *p = NULL;
    const char *q = NULL;
    const char *e = NULL;

    p = msg;
    e = p + len;


    q = p;
    while (q != e) {
        if (*q == '\n')
            break;
        q++;
    }

    while (q != e) {


        if (self->s) {


            int m = 0;
            int n = 0;
            char *s = NULL;

            m = self->l;
            n = m+q-p+1;

            s = (char *)malloc(n);
            memcpy(s, self->s, m);
            memcpy(s+m, p, q-p);
            s[n-1] = '\0';

            free(self->s);
            self->s = NULL;
            self->l = 0;

            Log_call(self, s, n-1);

            free(s);
        }
        else {
            int n = 0;
            char *s = NULL;

            n = q-p+1;

            s = (char *)malloc(n);
            memcpy(s, p, q-p);
            s[n-1] = '\0';

            Log_call(self, s, n-1);

            free(s);
        }

        p = q+1;


        q = p;
        while (q != e) {
            if (*q == '\n')
                break;
            q++;
        }
    }

    if (p != e) {


        if (self->s) {


            int m = 0;
            int n = 0;

            m = self->l;
            n = m+e-p+1;

            self->s = (char *)realloc(self->s, n);
            memcpy(self->s+m, p, e-p);
            self->s[n-1] = '\0';
            self->l = n-1;
        }
        else {
            int n = 0;

            n = e-p+1;

            self->s = (char *)malloc(n);
            memcpy(self->s, p, n-1);
            self->s[n-1] = '\0';
            self->l = n-1;
        }
    }
}
