DrucViewEqui ( Rectangle )
    rdsrec_list **Rectangle;
{
DrucTypeStructPlusRect *PlusRec1;
rdsrec_list            *RectangleCourant;

  RectangleCourant         = *Rectangle;
  PlusRec1                 = (DrucTypeStructPlusRect *)
                               ((char *)(RectangleCourant)+sizeof(rdsrec_list));
fprintf ( stdout,
          "\nEqui:\n"
        );
  while ( PlusRec1->NEXT_EQUI != *Rectangle
        )
  {
    RectangleCourant->FLAGS |= DRUC_FLAG_REC_VISITE;

    DrucViewRectangle (  & RectangleCourant
                      );
    RectangleCourant     = PlusRec1->NEXT_EQUI;
    PlusRec1             = (DrucTypeStructPlusRect *)
                               ((char *)(RectangleCourant)+sizeof(rdsrec_list));
  }
  RectangleCourant->FLAGS |= DRUC_FLAG_REC_VISITE;
  DrucViewRectangle (  & RectangleCourant
                    );
fprintf ( stdout,
          "\nFin Equi:\n"
        );
}
