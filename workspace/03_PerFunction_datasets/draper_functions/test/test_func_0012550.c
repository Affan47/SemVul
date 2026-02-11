DrucConcateneErrorFigures ( DrucFigureRds,
                                 DrucFigureRdsErreur
                               )
     rdsfig_list *DrucFigureRds;
     rdsfig_list *DrucFigureRdsErreur;

{

rdsfig_list *InstanceModele;
rdsins_list *InstanceCourante;
rdsrec_list *RectangleCourant;
rdsrec_list *NouveauRectangle;
char        *TmpName;
int          IndexLayer;

DrucViewString      ( "Merge Error Instances:"
                    );
    DrucViewString      ( "\n"
                        );

  for ( InstanceCourante  = DrucFigureRds->INSTANCE;
        InstanceCourante != (rdsins_list *)NULL;
        InstanceCourante  = InstanceCourante->NEXT
      )
  {


    TmpName = DrucAddSuffixeName ( InstanceCourante->FIGNAME,
                                   DRUC_ERROR_EXTEND
                                 );

    InstanceModele = searchrdsfig( TmpName
                                 );

    if ( InstanceModele == (rdsfig_list *)NULL
       )
    {
      continue;
    }
    DrucViewString      ( TmpName
                        );
    DrucViewString      ( "\n"
                        );

    for ( IndexLayer  = 0;
          IndexLayer  < RDS_MAX_LAYER;
          IndexLayer ++
        )
    {
      if ( ( IndexLayer == DRUC_BBOX ) ||
           ( IndexLayer == RDS_USER0 ) ||
           ( IndexLayer == RDS_USER1 ) ||
           ( IndexLayer == RDS_USER2 ) ||
           ( IndexLayer == RDS_USER3 ) ||
           ( IndexLayer == RDS_USER4 ) ||
           ( IndexLayer == RDS_USER5 ) ||
           ( IndexLayer == RDS_USER6 ) ||
           ( IndexLayer == RDS_USER7 ) ||
           ( IndexLayer == RDS_USER8 ) ||
           ( IndexLayer == RDS_USER9 )
         )
      {
        continue;
      }

      for ( RectangleCourant  = InstanceModele->LAYERTAB [ IndexLayer ];
            RectangleCourant != (rdsrec_list *)NULL;
            RectangleCourant  = RectangleCourant->NEXT
          )
      {
        NouveauRectangle = addrdsfigrec ( DrucFigureRdsErreur,
                                          RectangleCourant->NAME,
                                          IndexLayer,
                                          RectangleCourant->X,
                                          RectangleCourant->Y,
                                          RectangleCourant->DX,
                                          RectangleCourant->DY
                                        );

        applyrdssym ( & NouveauRectangle->X,
                      & NouveauRectangle->Y,
                      & NouveauRectangle->DX,
                      & NouveauRectangle->DY,
                      InstanceCourante->X,
                      InstanceCourante->Y,
                      InstanceCourante->TRANSF
                    );
      }
    }
  }
}
