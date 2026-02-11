DrucInitDefineLayerDest (Name)
     char *Name;
{
  int IndexLayer = 0;

  while( IndexLayer < RDS_MAX_LAYER )
  {
    if ( strstr( RDS_LAYER_NAME[ IndexLayer ] , Name ) != ( char *) NULL )
    {


      if ( DrucStructRdsLayer [ IndexLayer ].FLAGS == DRUC_FLAG_LAYER_INTERDIT )
      {
        DRUC_EXIT( DRUC_ERROR_NOT_DECLARED_LAYER);
      }


      if ( DrucStructRdsLayer [ IndexLayer ].FLAGS == DRUC_FLAG_LAYER_OCCUPE &&
           DrucStructDefine.OP_COMPOSE             != DRUC_COMPOSE_RESIZE
         )
      {
        DRUC_EXIT( DRUC_ERROR_NOT_EMPTY_LAYER);
      }
      else
      {
        DrucStructDefine.LAYER_DEST = IndexLayer;
        DrucStructRdsLayer [ IndexLayer ].FLAGS = DRUC_FLAG_LAYER_OCCUPE;
        return;
      }
    }
    IndexLayer ++ ;
  }


  if ( DrucStructDefine.USER_LAYER_NAME_0 != (char *)NULL )
  {
    if ( strstr( Name , DrucStructDefine.USER_LAYER_NAME_0 ) != (char *)NULL )
    {
      DRUC_EXIT( DRUC_ERROR_DEFINE_USER_LAYER);
    }
  }
  if ( DrucStructDefine.USER_LAYER_NAME_1 != (char *)NULL )
  {
    if ( strstr( Name , DrucStructDefine.USER_LAYER_NAME_1 ) != (char *)NULL )
    {
      DRUC_EXIT( DRUC_ERROR_DEFINE_USER_LAYER);
    }
  }
  if ( DrucStructDefine.USER_LAYER_NAME_2 != (char *)NULL )
  {
    if ( strstr( Name , DrucStructDefine.USER_LAYER_NAME_2 ) != (char *)NULL )
    {
      DRUC_EXIT( DRUC_ERROR_DEFINE_USER_LAYER);
    }
  }


  if ( DrucStructDefine.USER_LAYER_NAME_0 != (char *)NULL )
  {
    if ( DrucStructDefine.USER_LAYER_NAME_1 != (char *)NULL )
    {
      if ( DrucStructDefine.USER_LAYER_NAME_2 != (char *)NULL )
      {
        DRUC_EXIT( DRUC_ERROR_DEFINE_USER_LAYER );
      }
      DrucStructRdsLayer [ DRUC_USER_LAYER_2 ].FLAGS = DRUC_FLAG_LAYER_OCCUPE;
      DrucStructDefine.LAYER_DEST        = DRUC_USER_LAYER_2;
      DrucStructDefine.USER_LAYER_2      = DRUC_USER_LAYER_2;
      DrucStructDefine.USER_LAYER_NAME_2 = (char *)malloc ( strlen ( Name ) +1 );
      strcpy ( DrucStructDefine.USER_LAYER_NAME_2 ,Name );
      return;
    }
    DrucStructRdsLayer [ DRUC_USER_LAYER_1 ].FLAGS = DRUC_FLAG_LAYER_OCCUPE;
    DrucStructDefine.LAYER_DEST        = DRUC_USER_LAYER_1;
    DrucStructDefine.USER_LAYER_1      = DRUC_USER_LAYER_1;
    DrucStructDefine.USER_LAYER_NAME_1 = (char *)malloc ( strlen ( Name ) +1 );
    strcpy ( DrucStructDefine.USER_LAYER_NAME_1 ,Name );
    return;
  }
  DrucStructRdsLayer [ DRUC_USER_LAYER_0 ].FLAGS = DRUC_FLAG_LAYER_OCCUPE;
  DrucStructDefine.LAYER_DEST        = DRUC_USER_LAYER_0;
  DrucStructDefine.USER_LAYER_0      = DRUC_USER_LAYER_0;
  DrucStructDefine.USER_LAYER_NAME_0 = (char *)malloc ( strlen ( Name ) +1 );
  strcpy ( DrucStructDefine.USER_LAYER_NAME_0 ,Name );
}
