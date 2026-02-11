EXPkeepit(char *Entry, time_t when, time_t expires)
{
    NEWSGROUP           *ngp;
    enum KRP            retval = Remove;

    if ((ngp = NGfind(Entry)) == NULL)
        ngp = EXPnotfound(Entry);


    if (when > OVrealnow + 86400) {

        when = expires ? ngp->Purge : ngp->Default;
    }


    if (expires == 0) {
        if (when >= ngp->Default)
            retval = Keep;


    } else {
        if (when >= ngp->Purge && (expires >= OVnow || when >= ngp->Keep))
            retval = Keep;
    }
    if (retval == Keep) {
        return Keep;
    } else {
        return ngp->Poison ? Poison : Remove;
    }
}
