gethandlerlist(dacport, list_handler, end_handler, hlist_cnt)
u_short dacport;
handlerinfo_t **list_handler, **end_handler;
int *hlist_cnt;
{
        dac_gethandlerlist_ot in;
        handlerinfo_t *p_q;
        int sockdac;
        int i, j, k;
        u_short op;

        i = j = k = 0;

        if ((sockdac = connect_dac(dacport)) != -1) {
            op = htons(DAC_OP_GETHANDLERLIST);
            if (writen(sockdac, (char *)&op, sizeof(u_short)))
                if (readn(sockdac, (char *)&in, sizeof(dac_gethandlerlist_ot))) {
                    in.hlist_cnt = ntohs(in.hlist_cnt);
                    (*hlist_cnt) = in.hlist_cnt;
                    if (in.hlist_cnt > 0) {
                        while ((*hlist_cnt) > BUFFE_SIZE * j) {
                            j++;
                            for ( ; i < BUFFE_SIZE * j && i < (*hlist_cnt); i ++) {
                                p_q = (handlerinfo_t *) malloc(sizeof(handlerinfo_t));
				if (p_q == NULL)
				{
				    perror("DACLIB. gethandlerlist. Cannot malloc");
                                    exit(E_MALLOC);
				}
                                k = i - BUFFE_SIZE * (j - 1);
                                strcpy(p_q->name, (in.buffer[k]).name);
                                strcpy(p_q->login, (in.buffer[k]).login);
                                strcpy(p_q->mapid, (in.buffer[k]).mapid);
                                strcpy(p_q->inet_addr, (in.buffer[k]).inet_addr);
                                p_q->host = (in.buffer[k]).host;
                                p_q->type = (in.buffer[k]).type;
                                p_q->port = (in.buffer[k]).port;
                                p_q->next = NULL;
                                if (i == 0)
                                    (*list_handler) = (*end_handler) = p_q;
                                else {
                                    (*list_handler)->next = p_q;
                                    (*list_handler) = p_q;
                                }
                            }
                            if ((*hlist_cnt) > BUFFE_SIZE * j)
                                if (!readn(sockdac, (char *)&in, sizeof(dac_gethandlerlist_ot)))
                                    break;
                        }
                    } else {
                        printf("\n\n\t\t\t No handler found.\n");
                        return 0;
                    }
                    close(sockdac);
                    return 1;
                }
        }
        printf("Lost communication with DAC.\n");
        return 0;
}
