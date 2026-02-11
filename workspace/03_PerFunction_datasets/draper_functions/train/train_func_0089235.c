NextEngineCmd( void )
{
  char engineinput[BUF_SIZE]="";
  char enginemovestr[BUF_SIZE]="";
  leaf* enginemove;

  if ( strlen( engineinputbuf ) > 0 ) {
    if ( GetNextLine( engineinputbuf, engineinput ) > 0 ) {
      dbg_printf("< ENGINE: %s\n", engineinput);
      if ( strncmp( engineinput, "move", 4 ) == 0 ) {

        sscanf( engineinput, "move %s", enginemovestr );
        enginemove = ValidateMove( enginemovestr );
        if ( enginemove == (leaf *) NULL ) {
          dbg_printf( "Bad move from engine\n" );
        } else {
          dbg_printf( "Engine move: <%s> (%d,%d)\n", enginemovestr,
                      (enginemove!=NULL ? enginemove->move : -1),
                      (enginemove!=NULL ? enginemove->score : -1) );
          SANMove (enginemove->move, 1);
          MakeMove( board.side, &(enginemove->move) );
          strcpy (Game[GameCnt].SANmv, SANmv);
	  if ( !(flags & XBOARD) ) {
		  ShowBoard();
                  dbg_printf("USER <: My move is : %s\n", SANmv);
		  printf( "\nMy move is : %s\n", SANmv );
                  fflush( stdout );
	  } else {
                  dbg_printf("USER <: %d. ... %s\n", GameCnt/2 + 1, enginemovestr );
                  printf ("%d. ... %s\n", GameCnt/2 + 1, enginemovestr );
                  fflush( stdout );
                  dbg_printf("USER <: My move is : %s\n", enginemovestr);
		  printf( "My move is : %s\n", enginemovestr );
                  fflush( stdout );
          }
          RealGameCnt = GameCnt;
          showprompt = 1;

          if ( changeColor ) {
            RealGameCnt = GameCnt;
            RealSide = board.side;
          }
        }
      } else {
        dbg_printf( "USER <: %s\n",engineinput );
        printf( "%s", engineinput );
        if ( flags & XBOARD ) {
          fflush( stdout );
        }
      }
    }
  }
}
