ConfigureSession(player *p)
{
    char buf[1024];
    simplemsg *m;

    D(bug("Aspetto il ping...\n"));

    if(!(m=GetNextMsg(p)))
        return FALSE;

    if(m->type==MSG_PING) {
        short l=m->size;
        D(bug("Ping ricevuto...\n"));
        m->type=MSG_PONG;
        m->size=htons(l);
        SockWrite(p->socket,m,l+sizeof(simplemsg));
    }
    else
        return FALSE;

    UpdateNetStatus("WAITING FOR CONFIGURATION...");

    D(bug("Aspetto la configurazione...\n"));

    if(!(m=GetNextMsg(p)))
        return FALSE;

    if(m->type==MSG_CONFIG) {
        FILE *f;
        simplemsg msg;

        p->num=m->subtype;

        D(bug("Config ricevuta...il giocatore e' il plr %d\n",p->num));

        memcpy(msg.hdr,SERVER_HEADER,4);
        msg.subtype=0;
        msg.size=0;

        snprintf(buf, 1024, "%stempconfig", TEMP_DIR);
        if ((f=fopen(buf,"wb+"))) {
            extern void load_config(FILE *);

            fwrite(((char *)m) + sizeof(simplemsg), 1, m->size, f);

            D(bug("Scrivo %d bytes in tempconfig...\n", m->size));

            msg.type=MSG_OK;
            fseek(f,0,SEEK_SET);
            D(bug("Carico la configurazione...\n"));
            load_config(f);

        }
        else
            msg.type=MSG_KO;

        SockWrite(p->socket,&msg,sizeof(simplemsg));
    }
    return TRUE;
}
