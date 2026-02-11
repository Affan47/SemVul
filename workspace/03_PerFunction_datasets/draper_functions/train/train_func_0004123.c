DrucFlattenInstanceRings ( DrucFigureRds
                              )
     rdsfig_list *DrucFigureRds;
{
rdsfig_list               *InstanceModele;
rdsins_list               *InstanceCourante;
long                       PositionBboxX;
long                       PositionBboxY;
long                       PositionBboxDX;
long                       PositionBboxDY;
int                        IndexLayer;
char                      *TmpName;
char                      *savName;
char                      *brico = "a";
rdsrec_list               *RectangleCourant;
rdsrec_list               *NouveauRectangle;

DrucViewString ("Flatten Instance Rings:");
    for ( InstanceCourante  = DrucFigureRds->INSTANCE;
          InstanceCourante != (rdsins_list *)NULL;
          InstanceCourante  = InstanceCourante->NEXT
        )
    {


      TmpName = DrucAddSuffixeName ( InstanceCourante->FIGNAME,
                                     DRUC_COURONNE_EXTEND
                                   );
DrucViewString ("\r");
DrucViewString (TmpName);
DrucViewString ("                      ");
      InstanceModele = searchrdsfig( TmpName
                                   );


      for ( IndexLayer  = 0;
            IndexLayer  < RDS_MAX_LAYER;
            IndexLayer ++
          )
      {
        if ( ( IndexLayer == DRUC_BBOX ) ||
             ( IndexLayer == RDS_ABOX  ) ||
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
          NouveauRectangle = addrdsfigrec ( DrucFigureRds,
				            RectangleCourant->NAME,
                                            IndexLayer,
				            RectangleCourant->X,
				            RectangleCourant->Y,
		 		            RectangleCourant->DX,
				            RectangleCourant->DY
			                  );
          applyrdssym ( & (NouveauRectangle->X),
                        & (NouveauRectangle->Y),
                        & (NouveauRectangle->DX),
                        & (NouveauRectangle->DY),
                          InstanceCourante->X,
                          InstanceCourante->Y,
                          InstanceCourante->TRANSF
                      );
          MACRO_INSTANCE_NUM ( NouveauRectangle ) = InstanceCourante;


        }
      }


      for ( RectangleCourant  = InstanceModele->LAYERTAB [ RDS_ABOX ];
            RectangleCourant != (rdsrec_list *)NULL;
            RectangleCourant  = RectangleCourant->NEXT
          )
      {
        NouveauRectangle = addrdsfigrec ( DrucFigureRds,
                                          RectangleCourant->NAME,
                                          DRUC_BBOX,
                                          RectangleCourant->X,
                                          RectangleCourant->Y,
                                          RectangleCourant->DX,
                                          RectangleCourant->DY
                                        );
        applyrdssym ( & (NouveauRectangle->X),
                      & (NouveauRectangle->Y),
                      & (NouveauRectangle->DX),
                      & (NouveauRectangle->DY),
                        InstanceCourante->X,
                        InstanceCourante->Y,
                        InstanceCourante->TRANSF
                    );
        MACRO_INSTANCE_NUM ( NouveauRectangle ) = InstanceCourante;
      }
    }
DrucViewString ("\n");
}
