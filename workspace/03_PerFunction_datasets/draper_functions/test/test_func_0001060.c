DrucCaracteriseTesteSurface ( TmpRectangle,
                                   DrucInstructionCourante,
                                   IndexMesure
                                 )
rdsrec_list *TmpRectangle;
DrucTypeStructInstruction *DrucInstructionCourante;
int                        IndexMesure;

{
DrucTypeStructPlusRect *PlusRec;
DrucTypeStructMesure    DrucStructMesure;
rdsrec_list            *RectangleCourant;

  DrucStructMesure.LAYER_1    = DrucInstructionCourante->LAYER_1;
  DrucStructMesure.LAYER_2    = DrucInstructionCourante->LAYER_1;
  DrucStructMesure.RECTANGLE1 = TmpRectangle;
  PlusRec                     = (DrucTypeStructPlusRect *)((char *)(TmpRectangle)+sizeof(rdsrec_list));
  RectangleCourant            = PlusRec->NEXT_EQUI;
  PlusRec                     = (DrucTypeStructPlusRect *)((char *)(RectangleCourant)+sizeof(rdsrec_list));
  while ( TmpRectangle != RectangleCourant )
  {
    if ( DrucIsRectanglesContact ( TmpRectangle,
                                   RectangleCourant
                                 )
         == DRUC_TRUE
       )
    {
      DrucStructMesure.RECTANGLE2 = RectangleCourant;
      DrucRelationMesure ( &DrucStructMesure
                         );
      DrucMesureInter ( &DrucStructMesure,
                         DrucInstructionCourante,
                         IndexMesure,
                         MACRO_SURFACE_INTER_1
                       );
    }
    RectangleCourant = PlusRec->NEXT_EQUI;
    PlusRec          = (DrucTypeStructPlusRect *)((char *)(RectangleCourant)+sizeof(rdsrec_list));
  }
}
