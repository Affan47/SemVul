ScanJoysticks( struct InputPort *in )
{
	int i;
	int port = 0;


	memcpy( mJoyPrevious, mJoyCurrent, sizeof(mJoyPrevious) );


	memset( mJoyCurrent, 0, sizeof(mJoyCurrent) );


	while( in->type != IPT_END && port < MAX_INPUT_PORTS )
	{
		while (in->type != IPT_END && in->type != IPT_PORT)
		{
			if ((in->type & ~IPF_MASK) >= IPT_JOYSTICK_UP &&
				(in->type & ~IPF_MASK) <= IPT_JOYSTICKLEFT_RIGHT)
			{
				InputSeq* seq;
				seq = input_port_seq(in);
				if( seq_pressed(seq) )
				{
					int joynum,joydir,player;
					player = IP_GET_PLAYER(in);

					joynum = player * MAX_JOYSTICKS +
							 ((in->type & ~IPF_MASK) - IPT_JOYSTICK_UP) / 4;
					joydir = ((in->type & ~IPF_MASK) - IPT_JOYSTICK_UP) % 4;

					mJoyCurrent[joynum] |= 1<<joydir;
				}
			}
			in++;
		}
		port++;
		if (in->type == IPT_PORT) in++;
	}


	for( i=0; i<MAX_JOYSTICKS*MAX_PLAYERS; i++ )
	{
		if( (mJoyCurrent[i]&0x3)==0x3 )
		{
			mJoyCurrent[i]&=0xc;
		}
		if( (mJoyCurrent[i]&0xc)==0xc )
		{
			mJoyCurrent[i]&=0x3;
		}


		if( mJoyCurrent[i]!=mJoyPrevious[i] )
		{
			mJoy4Way[i] = mJoyCurrent[i];

			if( (mJoy4Way[i] & 0x3) && (mJoy4Way[i] & 0xc) )
			{


				mJoy4Way[i] ^= (mJoy4Way[i] & mJoyPrevious[i]);
			}

			if( (mJoy4Way[i] & 0x3) && (mJoy4Way[i] & 0xc) )
			{


				if( rand()&1 )
				{
					mJoy4Way[i] &= 0x3;
				}
				else
				{
					mJoy4Way[i] &= 0xc;
				}
			}
		}
	}
}
