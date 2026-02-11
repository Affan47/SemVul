STRinit(String *st)
{
     if (st != NULL) {
	  if (st->len > 0)
	       st->len  = - st->len;


     } else
	  perror("STRinit, non existant string!");
}
