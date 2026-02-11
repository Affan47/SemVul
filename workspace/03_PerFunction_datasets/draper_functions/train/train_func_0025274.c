tanplacepiecefloat (tanpiecepos *piecepos, tanfpnt *fpnts, double zoom){

  int i;
  tanpiecedef *piecedat;
  double lx,ly,lx2,cosrot,sinrot;
  int rot;
  int nbr;

  piecedat=&piecesdef[piecepos->type];
  nbr=piecedat->pntnbr;
  rot=piecepos->rot;
  cosrot=cos(rot*PASTOUR);
  sinrot=sin(rot*PASTOUR);

  for(i=0; i<nbr; i++){
    lx2=piecedat->pnt[i].posx-piecedat->handlex;
    ly=piecedat->pnt[i].posy-piecedat->handley;
    if (piecepos->flipped)
      lx2=-lx2;
    lx=(piecepos->posx+lx2*cosrot+ly*sinrot)*zoom;
    ly=(piecepos->posy+ly*cosrot-lx2*sinrot)*zoom;
    fpnts->posx=lx;
    fpnts++->posy=ly;
  }
  fpnts -=nbr;

  if (piecepos->flipped){
    tanfpnt dumfpnt;
    for (i = 0; i<nbr/2 ;i++){
      dumfpnt = fpnts[i];
      fpnts[i] = fpnts[nbr-i-1];
      fpnts[nbr-i-1] = dumfpnt;
    }
  }

  *(fpnts+nbr)=*fpnts;

  return(nbr);

}
