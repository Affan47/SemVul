get_cumprinc  (gnm_float fRate, gint nNumPeriods, gnm_float fVal,
	       gint nStart, gint nEnd, gint nPayType)
{
        gnm_float fRmz, fKapZ;
	gint       i;

        fRmz = GetRmz ( fRate, nNumPeriods, fVal, 0.0, nPayType );

        fKapZ = 0.0;

	if ( nStart == 1 ) {
                if ( nPayType <= 0 )
                        fKapZ = fRmz + fVal * fRate;
                else
                        fKapZ = fRmz;

		nStart++;
        }

	for ( i = nStart ; i <= nEnd ; i++ ) {
                if ( nPayType > 0 )
                        fKapZ += fRmz - ( GetZw ( fRate, ( i - 2 ), fRmz,
						  fVal, 1 ) - fRmz ) * fRate;
                else
                        fKapZ += fRmz - GetZw( fRate, ( i - 1 ), fRmz, fVal,
					       0 ) * fRate;
        }

	return value_new_float ( fKapZ );
}
