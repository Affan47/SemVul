DrucMin ( DrucFigureRds,
               DrucRdsWindow,
               DrucTabInstruction ,
               DrucNombreInstructions
             )
     rdsfig_list               *DrucFigureRds;
     rdswindow                 *DrucRdsWindow;
     DrucTypeStructInstruction *DrucTabInstruction;
     int                        DrucNombreInstructions;

{

int             InstructionCourante;

DrucViewString ( "instructionCourante : 000"
               );


  for ( InstructionCourante = 0;
        InstructionCourante != DrucNombreInstructions;
        InstructionCourante = InstructionCourante + 1
      )
  {

    DrucViewString       ( "\b\b\b"
                         );
    DrucViewNumber       ( InstructionCourante
                         );


    if ( MACRO_REGLE_COURANTE.LAYER_1 == DRUC_UNDEFINED_LAYER
       )
    {


      continue;
    }

    switch ( MACRO_REGLE_COURANTE.INSTRUCTION
           )
    {
    case  DRUC_ASM_BEGIN_REGLE :
      {
        switch ( MACRO_REGLE_COURANTE.OP_COMPOSE
               )
        {
        case DRUC_INSTR_RELATION :
          {
            DrucRelation (   DrucFigureRds,
                             DrucRdsWindow,
                           & MACRO_REGLE_COURANTE
                         );
            break;
          }
        case DRUC_INSTR_CARACTERISE :
          {

            DrucCaracterise (   DrucFigureRds,
                              & MACRO_REGLE_COURANTE
                            );
            break;
          }
        }
        break;
      }
    case  DRUC_ASM_BEGIN_DEFINE :
      {
        DrucDefine (   DrucFigureRds,
                       DrucRdsWindow ,
                     & MACRO_REGLE_COURANTE
                   );
        break;
      }
    case  DRUC_ASM_BEGIN_UNDEFINE:
      {
        DrucUndefine (   DrucFigureRds,
                         DrucRdsWindow,
                       & MACRO_REGLE_COURANTE
                     );
        break;
      }
    }
  }

DrucViewString ( "\n"
               );


}
