PassEdge(const eWall *ww,REAL time,REAL a,int r)
        {
            try{
                gSensor::PassEdge(ww,time,a,r);
            }
            catch( eSensorFinished & e )
            {
                if ( DoExtraDetectionStuff() )
                    throw;
            }
        }
