WCHANremove(CHANNEL *cp)
{
    if (FD_ISSET(cp->fd, &channels.write_set)) {
        FD_CLR(cp->fd, &channels.write_set);
        CHANresetlast(cp->fd);


        if (cp->Out.left <= 0) {
            cp->Out.used = 0;
            cp->Out.left = 0;
        }
    }
}
