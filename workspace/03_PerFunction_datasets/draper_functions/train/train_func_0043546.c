cirdna_DrawTicks(float xDraw, float yDraw, float RealLength,
			     float Radius, float TickHeight, float From,
			     const AjPStr Name2, float OriginAngle,
			     float postext,
			     const AjPStr PosTicks,
			     ajint NumNames, ajint Adjust,
			     ajint Colour)
{
    float Angle;
    float StartAngle;
    float EndAngle;
    float *xy1;
    float *xy2;
    float *xy3;
    float stringLength;
    float r1Ticks = Radius;
    float r2Ticks = r1Ticks+TickHeight;
    const AjPStr token;
    float mmtolen;


    mmtolen = RealLength/(Radius * (float) 2.0 * (float) 3.1416);

    ajGraphicsSetFgcolour(Colour);

    Angle = cirdna_ComputeAngle(RealLength, From, OriginAngle);

    xy1 = ajGraphicsCalcCoord(xDraw, yDraw, r1Ticks, Angle);
    xy2 = ajGraphicsCalcCoord(xDraw, yDraw, r2Ticks, Angle);
    ajGraphicsDrawposLine(xy1[0], xy1[1], xy2[0], xy2[1] );
    AJFREE(xy1);
    AJFREE(xy2);

    if(ajStrMatchCaseC(PosTicks, "In") )
    {
	stringLength = mmtolen * cirdna_HorTextPileLengthMax(Name2, NumNames);
	StartAngle = cirdna_ComputeAngle(RealLength, From+stringLength/2,
					 OriginAngle);
	EndAngle = cirdna_ComputeAngle(RealLength, From-stringLength/2,
				       OriginAngle);
	cirdna_HorTextPile(xDraw, yDraw, r2Ticks+(Adjust*postext), StartAngle,
			   EndAngle, Name2, postext, 1);
    }
    else
    {
	token = ajStrParseC(Name2, ";");

	stringLength = mmtolen * ajGraphicsCalcTextlengthS(token);
	xy1 = ajGraphicsCalcCoord(xDraw, yDraw, r2Ticks+postext, Angle);
	xy2 = ajGraphicsCalcCoord(xDraw, yDraw, r2Ticks+postext+stringLength,
			     Angle);
	xy3 = ajGraphicsCalcCoord(xDraw, yDraw, r2Ticks+postext-stringLength,
			     Angle);
	if((Angle>=0.0 && Angle<=90.0) || (Angle>=270.0 && Angle<=360.0) ||
	   (Angle>=360.0 && Angle<=450.0) || (Angle>=630.0 && Angle<=720.0) )
	    ajGraphicsDrawposTextAtlineJustify( xy1[0], xy1[1], xy2[0], xy2[1],
                                                ajStrGetPtr(token), 0.0 );
	else
	    ajGraphicsDrawposTextAtlineJustify( xy1[0], xy1[1], xy3[0], xy3[1],
                                                ajStrGetPtr(token), 1.0 );
	AJFREE(xy1);
	AJFREE(xy2);
	AJFREE(xy3);
    }

    return;
}
