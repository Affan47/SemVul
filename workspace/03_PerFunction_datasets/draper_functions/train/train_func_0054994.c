namcos3d_Rotate( double M[4][4], const struct RotParam *pParam )
{
	switch( pParam->rolt )
	{
	case 0:
		matrix3d_RotX( M, pParam->thx_sin, pParam->thx_cos );
		matrix3d_RotY( M, pParam->thy_sin, pParam->thy_cos );
		matrix3d_RotZ( M, pParam->thz_sin, pParam->thz_cos );
		break;
	case 1:
		matrix3d_RotX( M, pParam->thx_sin, pParam->thx_cos );
		matrix3d_RotZ( M, pParam->thz_sin, pParam->thz_cos );
		matrix3d_RotY( M, pParam->thy_sin, pParam->thy_cos );
		break;
	case 2:
		matrix3d_RotY( M, pParam->thy_sin, pParam->thy_cos );
		matrix3d_RotX( M, pParam->thx_sin, pParam->thx_cos );
		matrix3d_RotZ( M, pParam->thz_sin, pParam->thz_cos );
		break;
	case 3:
		matrix3d_RotY( M, pParam->thy_sin, pParam->thy_cos );
		matrix3d_RotZ( M, pParam->thz_sin, pParam->thz_cos );
		matrix3d_RotX( M, pParam->thx_sin, pParam->thx_cos );
		break;
	case 4:
		matrix3d_RotZ( M, pParam->thz_sin, pParam->thz_cos );
		matrix3d_RotX( M, pParam->thx_sin, pParam->thx_cos );
		matrix3d_RotY( M, pParam->thy_sin, pParam->thy_cos );
		break;
	case 5:
		matrix3d_RotZ( M, pParam->thz_sin, pParam->thz_cos );
		matrix3d_RotY( M, pParam->thy_sin, pParam->thy_cos );
		matrix3d_RotX( M, pParam->thx_sin, pParam->thx_cos );
		break;
	default:
		logerror( "unknown rolt:%08x\n",pParam->rolt );
		break;
	}
}
