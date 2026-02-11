find_string(const char *str,const char *key)
{
    const char *p1,*p2;
    for (p1=str,p2=key;*p1;) {
        if (!*p2) {
            return (char*)(str);
        }else{
            if (*p2==*p1){
                p1 ++; p2++;
            }else{
                p2 = key;
                p1 = (++str);
            }
        }
    }
    if (!*p2) return (char*)(str);
    return 0;
}
