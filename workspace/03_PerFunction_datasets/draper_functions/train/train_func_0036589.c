expandMacros(const char *str, struct expando *expandos)
{
    struct expando *ex;
    int cnt = 0, rcnt, vl;
    const char *sp = str;
    char *ret, *cp;
    char c;

  oke1:
    while ((c = *sp++)) {
        if (c == '%') {
            rcnt = 0;
            for (;;) {
                c = *sp++;
                if (!c)
                    goto murks1;
                if (c == '%')
                    break;
                for (ex = expandos; ex->key; ex++)
                    if (c == ex->key) {
                        if (ex->val)
                            cnt += strlen(ex->val) + rcnt;
                        goto oke1;
                    }
                rcnt++;
            }
        }
        cnt++;
    }
  murks1:
    if (!(cp = ret = Malloc(cnt + 1)))
        return 0;
  oke2:
    while ((c = *str++)) {
        if (c == '%') {
            rcnt = 0;
            for (;;) {
                c = *str++;
                if (!c)
                    goto murks2;
                if (c == '%')
                    break;
                for (ex = expandos; ex->key; ex++)
                    if (c == ex->key) {
                        if (ex->val) {
                            vl = strlen(ex->val);
                            memcpy(cp, str - 1 - rcnt, rcnt);
                            memcpy(cp + rcnt, ex->val, vl);
                            cp += vl + rcnt;
                        }
                        ex->uses++;
                        goto oke2;
                    }
                rcnt++;
            }
        }
        *cp++ = c;
    }
  murks2:
    *cp = 0;
    return ret;
}
