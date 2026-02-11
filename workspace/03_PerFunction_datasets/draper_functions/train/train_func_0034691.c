RS_SetTexcoords2D (rs_stage_t *stage, float *os, float *ot)
{
	float	txm = 0, tym = 0;


	if (stage->scale.scaleX)
	{
		switch (stage->scale.typeX)
		{
		case 0:
			*os *= stage->scale.scaleX;
			break;
		case 1:
			*os *= stage->scale.scaleX*sin(rs_realtime*0.05);
			break;
		case 2:
			*os *= stage->scale.scaleX*cos(rs_realtime*0.05);
			break;
		}
	}

	if (stage->scale.scaleY)
	{
		switch (stage->scale.typeY)
		{
		case 0:
			*ot *= stage->scale.scaleY;
			break;
		case 1:
			*ot *= stage->scale.scaleY*sin(rs_realtime*0.05);
			break;
		case 2:
			*ot *= stage->scale.scaleY*cos(rs_realtime*0.05);
			break;
		}

	}


	if (stage->rot_speed)
		RS_RotateST2 (os, ot, -stage->rot_speed * rs_realtime * 0.0087266388888888888888888888888889);

	if (stage->scroll.speedX)
	{
		switch(stage->scroll.typeX)
		{
			case 0:
				txm=rs_realtime*stage->scroll.speedX;
				break;
			case 1:
				txm=sin(rs_realtime*stage->scroll.speedX);
				break;
			case 2:
				txm=cos(rs_realtime*stage->scroll.speedX);
				break;
		}
	}
	else
		txm=0;

	if (stage->scroll.speedY)
	{
		switch(stage->scroll.typeY)
		{
			case 0:
				tym=rs_realtime*stage->scroll.speedY;
				break;
			case 1:
				tym=sin(rs_realtime*stage->scroll.speedY);
				break;
			case 2:
				tym=cos(rs_realtime*stage->scroll.speedY);
				break;
		}
	}
	else
		tym=0;

	*os += txm;
	*ot += tym;
}
