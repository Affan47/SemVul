tanloadfigtab (char *name){

 FILE *hand=NULL;
 int i,j;
 gboolean succes;
 int newfigtabsize;
 tanfigure *newfigtab=NULL,*figs;
 int lres;

 lres=0;

 if ( (hand = g_fopen(name, "r"))!=NULL &&
      fscanf(hand, "gTans v1.0 %d \n", &newfigtabsize)==1 &&
      (newfigtab = (tanfigure *)g_malloc(sizeof(tanfigure)*newfigtabsize))!=NULL ){

   lres=1;
   figs = newfigtab;
   for (i = 0; i<newfigtabsize; i++){
     *figs = figuredebut;
     figs->zoom = tanreadfloat(hand, &lres);
     figs->distmax = tanreadfloat(hand, &lres);
     SPESC(hand,"%d \n", &figs->drotmax);

     for (j=0; j<PIECENBR; j++){
       SPESC(hand,"p %d", &figs->piecepos[j].type);
       SPESC(hand,"%d", &figs->piecepos[j].flipped);
       figs->piecepos[j].posx = tanreadfloat(hand, &lres);
       figs->piecepos[j].posy = tanreadfloat(hand, &lres);
       SPESC(hand,"%d \n", &figs->piecepos[j].rot);


     }
     figs++;
   }
 } else
      g_warning("Opening file %s fails",name);

 if (hand!=NULL)
   fclose(hand);

 succes=FALSE;
 if (lres==1){
   succes=TRUE;

   if(figtab!=NULL)
     g_free(figtab);

   figtab=newfigtab;
   figtabsize=newfigtabsize;

   actual_figure = 0;

   tansetnewfigurepart1(actual_figure);
   tansetnewfigurepart2();


 }

 if (succes || figfilename==NULL)
   tanallocname(&figfilename, name);

 return(succes);

}
