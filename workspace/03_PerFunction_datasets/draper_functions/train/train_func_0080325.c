makeconnections (lofig, mark)

lofig_list *lofig;
unsigned char mark;


{
 loins_list *ptloins;
 locon_list *ptlocon;
 int result = OK;

 if (lofig == (struct lofig*)NULL) {
    error_count ++;
    printf ("\n\nNetlist %i is empty!\n", mark);
    return ( ERR );
    }


 for (ptlocon = lofig->LOCON; ptlocon != NULL; ptlocon = ptlocon->NEXT)
     result |= insertlocon (ptlocon, mark);


 for (ptloins = lofig->LOINS; ptloins != NULL; ptloins = ptloins->NEXT)
     for (ptlocon = ptloins->LOCON; ptlocon != NULL; ptlocon = ptlocon->NEXT)
         result |= insertlocon (ptlocon, mark);

 return ( result );
}
