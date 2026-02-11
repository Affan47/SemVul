GSplusInit(GopherObj *gs)
{
     if (gs->gplus != NULL) {
	  STRinit(gs->gplus->Admin);
	  STRinit(gs->gplus->ModDate);
	  VIAinit(gs->gplus->Views);
	  STAinit(gs->gplus->OtherBlocks);

     }
}
