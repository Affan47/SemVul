DrucIntersectRectangle ( DrucFigureRds,
                              DrucRdsWindow,
                              DrucInstructionCourante,
                              Rectangle1,
                              Rectangle2
                            )
              rdsfig_list               *DrucFigureRds;

              rdswindow                 *DrucRdsWindow;
              DrucTypeStructInstruction *DrucInstructionCourante;
     register rdsrec_list               *Rectangle1;
     register rdsrec_list               *Rectangle2;

{

register long         TmpDx1          = Rectangle1->X + Rectangle1->DX;
register long         TmpDy1          = Rectangle1->Y + Rectangle1->DY;
register long         TmpDx2          = Rectangle2->X + Rectangle2->DX;
register long         TmpDy2          = Rectangle2->Y + Rectangle2->DY;
register int          TmpLayerDest    = DrucInstructionCourante->LAYER_DEST;
         rdsrec_list *TmpRectangleDest;

  if ( ( TmpDx1 < Rectangle2->X ) ||
       ( TmpDx2 < Rectangle1->X )
     )
  {
    return;
  }

  if ( ( TmpDy1 < Rectangle2->Y ) ||
       ( TmpDy2 < Rectangle1->Y )
     )
  {
    return;
  }

  TmpRectangleDest       = allocrdsrec( sizeof
                                        ( DrucTypeStructPlusRect )
                                      );

  TmpRectangleDest->X    = ( ( Rectangle1->X < Rectangle2->X ) ?
                             Rectangle2->X :
                             Rectangle1->X
                           );

  TmpRectangleDest->Y    = ( ( Rectangle1->Y < Rectangle2->Y ) ?
                             Rectangle2->Y :
                             Rectangle1->Y
                           );

  TmpRectangleDest->DX   = ( ( TmpDx1 < TmpDx2 ) ?
                             TmpDx1 - TmpRectangleDest->X :
                             TmpDx2 - TmpRectangleDest->X
                           );
  TmpRectangleDest->DY   = ( ( TmpDy1 < TmpDy2 ) ?
                             TmpDy1 - TmpRectangleDest->Y :
                             TmpDy2 - TmpRectangleDest->Y
                           );
  SetRdsLayer       ( TmpRectangleDest ,
                      TmpLayerDest
                    );
  DrucChaineCompose ( TmpRectangleDest ,
                      Rectangle1,
                      DrucInstructionCourante->LAYER_1
                    );
  DrucChaineCompose ( TmpRectangleDest ,
                      Rectangle2,
                      DrucInstructionCourante->LAYER_2
                    );
  addrdsrecwindow   ( TmpRectangleDest ,
                      DrucRdsWindow
                    );
  DrucAddRecFigure  ( TmpRectangleDest ,
                      DrucFigureRds ,
                      TmpLayerDest
                    );
}
