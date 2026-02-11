sm_dump(bool bufdump)
{
	struct abufhead *ap;

	P(mutex);

	ap = (struct abufhead *) abqueue.qnext;

	while (ap != (struct abufhead *) &abqueue) {

	   if ((ap == NULL) ||
	       (ap->abq.qnext->qprev != (struct queue *) ap) ||
	       (ap->abq.qprev->qnext != (struct queue *) ap)) {
	      fprintf(stderr,
                 "\nOrphaned buffers exist.  Dump terminated following\n");
	      fprintf(stderr,
                 "  discovery of bad links in chain of orphaned buffers.\n");
	      fprintf(stderr,
                 "  Buffer address with bad links: %lx\n", (long) ap);
	      break;
	   }

	   if (ap->abfname != NULL) {
	      unsigned memsize = ap->ablen - (sizeof(struct abufhead) + 1);
	      char errmsg[512];

	      sprintf(errmsg,
                "Orphaned buffer:  %6u bytes allocated at line %d of %s\n",
		 memsize, ap->ablineno, ap->abfname
	      );
              fprintf(stderr, "%s", errmsg);
	      if (bufdump) {
		 unsigned llen = 0;
		 char *cp = ((char *) ap) + sizeof(struct abufhead);

		 errmsg[0] = EOS;
		 while (memsize) {
		    if (llen >= 16) {
                       strcat(errmsg, "\n");
		       llen = 0;
                       fprintf(stderr, "%s", errmsg);
		       errmsg[0] = EOS;
		    }
                    sprintf(errmsg + strlen(errmsg), " %02X",
		       (*cp++) & 0xFF);
		    llen++;
		    memsize--;
		 }
                 fprintf(stderr, "%s\n", errmsg);
	      }
	   }
	   ap = (struct abufhead *) ap->abq.qnext;
	}
	V(mutex);
}
