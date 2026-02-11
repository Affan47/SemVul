SetupWindow( const INT32 *pWindow, int which )
{
	if( which!=mPrevWindow )
	{
		double vw,vh;

		mPrevWindow = which;
		pWindow += which*0x80/4;

		vw = pWindow[0x3c/4];
		vh = pWindow[0x40/4];
		mCamera.cx  = 320+pWindow[0x54/4];
		mCamera.cy  = 240-pWindow[0x58/4];
		mCamera.clip.min_x = mCamera.cx - vw;
		mCamera.clip.min_y = mCamera.cy - vh;
		mCamera.clip.max_x = mCamera.cx + vw;
		mCamera.clip.max_y = mCamera.cy + vh;

		if( mCamera.clip.min_x <   0 ) mCamera.clip.min_x = 0;
		if( mCamera.clip.min_y <   0 ) mCamera.clip.min_y = 0;
		if( mCamera.clip.max_x > 640 ) mCamera.clip.max_x = 640;
		if( mCamera.clip.max_y < 320 ) mCamera.clip.max_y = 320;

		{

	        double fov = pWindow[0x38/4];

	        if( namcos22_gametype == NAMCOS22_PROP_CYCLE )
	        {
				fov /= 32.0;
			}
			fov = fov*3.141592654/180.0;
			mCamera.zoom = vw/tan(fov/2.0);
		}

		mWindowPri = pWindow[0x50/4]&0x7;

		matrix3d_Identity( mWindowTransform.M );
		ApplyRotation( &pWindow[1], mWindowTransform.M );

		mCamera.power   = (INT16)(pWindow[0x20/4])/(double)0xff;
		mCamera.ambient = (INT16)(pWindow[0x24/4])/(double)0xff;
		mCamera.x       = (INT16)(pWindow[0x28/4])/(double)0x7fff;
		mCamera.y       = (INT16)(pWindow[0x2c/4])/(double)0x7fff;
		mCamera.z       = (INT16)(pWindow[0x30/4])/(double)0x7fff;
	}
}
