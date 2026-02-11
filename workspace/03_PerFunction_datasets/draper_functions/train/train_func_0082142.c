JAM_LockMB( s_JamBase* Base_PS, int Timeout_I )
{
   if ( Base_PS->Locked_I )
		return 0;

   switch ( Timeout_I )
	{

      case -1:
			while ( jam_Lock( Base_PS, 1 ) == JAM_LOCK_FAILED )
	   	   JAM_Sleep( 1 );
			return 0;


      case 0:
			return jam_Lock( Base_PS, 1 );


      default:
			{
		   time_t Time_I = time(NULL) + Timeout_I;

	   	while ( time(NULL) < Time_I )
			{
	      	int Result_I;

	      	Result_I = jam_Lock( Base_PS, 1 );

	      	if ( Result_I == JAM_LOCK_FAILED )
		   		JAM_Sleep( 1 );
	      	else
		   		return Result_I;
	   	}
			return JAM_LOCK_FAILED;
      	}
    }
}
