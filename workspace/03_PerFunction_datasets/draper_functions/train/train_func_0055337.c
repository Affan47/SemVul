gagsdo (char *cmd, gaint *rc) {
gaint savflg,tlen,i;
struct gacmn *pcm;
char *mbuf, *ch;

   savflg = msgflg;
   msgflg = 1;
   pcm = savpcm;
   msgstk = NULL;

   *rc = gacmd(cmd, pcm, 0);


   if (msgstk==NULL) {
     msgflg = savflg;
     return(NULL);
   }

   tlen = 0;
   msgcurr = msgstk;
   while (msgcurr) {
     tlen += msgcurr->len;
     msgcurr = msgcurr->forw;
   }

   mbuf = (char *)malloc(tlen+1);
   if (mbuf==NULL) {
     printf ("Memory allocation error: Message Return Buffer\n");
     msgflg = savflg;
     return (NULL);
   }

   msgcurr = msgstk;
   ch = mbuf;
   while (msgcurr!=NULL) {
     for (i=0; i<msgcurr->len; i++) {
       *ch = *(msgcurr->msg+i);
       ch++;
     }
     msgcurr = msgcurr->forw;
   }
   msgcurr = msgstk;
   while (msgcurr!=NULL) {
     if (msgcurr->msg) free(msgcurr->msg);
     msgstk = msgcurr->forw;
     free(msgcurr);
     msgcurr = msgstk;
   }

   *(mbuf+tlen) = '\0';
   msgflg = savflg;
   return (mbuf);
}
