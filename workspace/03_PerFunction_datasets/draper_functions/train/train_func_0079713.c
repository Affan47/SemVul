Round(struct GPSPoint* First, struct GPSPoint* Result,
		struct CorrelateOptions* Options, time_t PhotoTime)
{


	struct GPSPoint* CopyFrom = NULL;


	double Scale = (double)First->Next->Time - (double)First->Time;
	Scale = ((double)PhotoTime - (double)First->Time) / Scale;


	if (Scale <= 0.5)
	{

		CopyFrom = First;
	} else {

		CopyFrom = First->Next;
	}


	Result->Lat = CopyFrom->Lat;
	Result->Long = CopyFrom->Long;
	Result->Elev = CopyFrom->Elev;
	Result->Time = CopyFrom->Time;


}
