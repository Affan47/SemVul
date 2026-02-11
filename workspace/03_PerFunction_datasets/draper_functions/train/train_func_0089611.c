DrealLoadParameters()

{
  char  Layer;
  char  Buffer[ 512 ];
  char *String;

  rdsbegin();

  DREAL_TECHNO_NAME = mbkgetenv( "DREAL_TECHNO_NAME" );

  if ( DREAL_TECHNO_NAME == (char *)NULL )
  {
    String = mbkgetenv( "ALLIANCE_TOP" );
    if ( String == (char *)NULL ) String = ALLIANCE_TOP;

    sprintf( Buffer, "%s/%s", String, DREAL_DEFAULT_TECHNO_NAME );
    DREAL_TECHNO_NAME = mbkstrdup( Buffer );
  }

  if ( ! KeywordDefined )
  {
    DefineKeyword             = namealloc( DEFINE_KEYWORD               );
    TableKeyword              = namealloc( TABLE_KEYWORD                );
    EndTableKeyword           = namealloc( END_TABLE_KEYWORD            );
    EndRecordKeyword          = namealloc( END_RECORD_KEYWORD           );
    RdsLayerNameKeyword       = namealloc( RDS_LAYER_NAME_KEYWORD       );
    LowerGridStepKeyword      = namealloc( LOWER_GRID_STEP_KEYWORD      );
    LowerFigureStepKeyword    = namealloc( LOWER_FIGURE_STEP_KEYWORD    );
    LowerInstanceStepKeyword  = namealloc( LOWER_INSTANCE_STEP_KEYWORD  );
    LowerReferenceStepKeyword = namealloc( LOWER_REFERENCE_STEP_KEYWORD );
    LowerSegmentStepKeyword   = namealloc( LOWER_SEGMENT_STEP_KEYWORD   );
    LowerConnectorStepKeyword = namealloc( LOWER_CONNECTOR_STEP_KEYWORD );
    CursorColorNameKeyword    = namealloc( CURSOR_COLOR_NAME_KEYWORD    );
    CursorSizeKeyword         = namealloc( CURSOR_SIZE_KEYWORD          );

    KeywordDefined = 1;
  }

  for ( Layer = 0; Layer < RDS_ALL_LAYER; Layer++ )
  {
    DREAL_RDS_LAYER_NAME_TABLE[ Layer ][0] = (char *)NULL;
    DREAL_RDS_LAYER_NAME_TABLE[ Layer ][1] = (char *)NULL;
    DREAL_RDS_LAYER_NAME_TABLE[ Layer ][2] = (char *)NULL;
    DREAL_RDS_LAYER_PATTERN_TABLE[ Layer ] = -1;
  }

  DREAL_LOWER_GRID_STEP       = 0.0;
  DREAL_LOWER_FIGURE_STEP     = 0.0;
  DREAL_LOWER_INSTANCE_STEP   = 0.0;
  DREAL_LOWER_CONNECTOR_STEP  = 0.0;
  DREAL_LOWER_SEGMENT_STEP    = 0.0;
  DREAL_LOWER_REFERENCE_STEP  = 0.0;
  DREAL_CURSOR_COLOR_NAME     = (char *)NULL;
  DREAL_CURSOR_SIZE           = 5;

  if ( !( GsbFile = fopen( DREAL_TECHNO_NAME, "r")))

    GsbError( OPEN_FILE, NULL, 0);

  GsbReadParam();

  fclose( GsbFile );

  DREAL_RDS_UNIT_TO_MICRON      = 1.0 / (float)( RDS_UNIT );
  DREAL_PHYSICAL_GRID_TO_MICRON = (float)( RDS_PHYSICAL_GRID ) / (float)( RDS_UNIT );

  rdsend();
}
