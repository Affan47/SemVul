float8_regr_accum(PG_FUNCTION_ARGS)
{
	ArrayType  *transarray = PG_GETARG_ARRAYTYPE_P(0);
	float8		newvalY = PG_GETARG_FLOAT8(1);
	float8		newvalX = PG_GETARG_FLOAT8(2);
	float8	   *transvalues;
	float8		N,
				sumX,
				sumX2,
				sumY,
				sumY2,
				sumXY;

	transvalues = check_float8_array(transarray, "float8_regr_accum", 6);
	N = transvalues[0];
	sumX = transvalues[1];
	sumX2 = transvalues[2];
	sumY = transvalues[3];
	sumY2 = transvalues[4];
	sumXY = transvalues[5];

	N += 1.0;
	sumX += newvalX;
	CHECKFLOATVAL(sumX, isinf(transvalues[1]) || isinf(newvalX), true);
	sumX2 += newvalX * newvalX;
	CHECKFLOATVAL(sumX2, isinf(transvalues[2]) || isinf(newvalX), true);
	sumY += newvalY;
	CHECKFLOATVAL(sumY, isinf(transvalues[3]) || isinf(newvalY), true);
	sumY2 += newvalY * newvalY;
	CHECKFLOATVAL(sumY2, isinf(transvalues[4]) || isinf(newvalY), true);
	sumXY += newvalX * newvalY;
	CHECKFLOATVAL(sumXY, isinf(transvalues[5]) || isinf(newvalX) ||
				  isinf(newvalY), true);


	if (AggCheckCallContext(fcinfo, NULL))
	{
		transvalues[0] = N;
		transvalues[1] = sumX;
		transvalues[2] = sumX2;
		transvalues[3] = sumY;
		transvalues[4] = sumY2;
		transvalues[5] = sumXY;

		PG_RETURN_ARRAYTYPE_P(transarray);
	}
	else
	{
		Datum		transdatums[6];
		ArrayType  *result;

		transdatums[0] = Float8GetDatumFast(N);
		transdatums[1] = Float8GetDatumFast(sumX);
		transdatums[2] = Float8GetDatumFast(sumX2);
		transdatums[3] = Float8GetDatumFast(sumY);
		transdatums[4] = Float8GetDatumFast(sumY2);
		transdatums[5] = Float8GetDatumFast(sumXY);

		result = construct_array(transdatums, 6,
								 FLOAT8OID,
								 sizeof(float8), FLOAT8PASSBYVAL, 'd');

		PG_RETURN_ARRAYTYPE_P(result);
	}
}
