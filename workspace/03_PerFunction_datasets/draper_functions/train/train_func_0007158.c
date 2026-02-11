collidesWithWeatherDataSet(double r, const WeatherData &wData, double thres)
{
    if(wData.size() == 0)
    {
        return false;
    }
    double x1;
    double y1;
    double z1;
    double cellWidth;
    double cellHeight;
    double deviationProbability;
    for(unsigned int i=0; i<wData.size() ; i++)
    {

        if(wData.getCellData(i, &x1, &y1, &z1, &deviationProbability, &cellWidth, &cellHeight))
        {
            if(deviationProbability <= thres)
            {
                continue;
            }
            if(z < z1 || z > z1+cellHeight)
            {
                continue;
            }
            else
            {
                double distanceInPixels = sqrt( (x-x1)*(x-x1) + (y-y1)*(y-y1) );
                double distanceInNM = distanceInPixels*NMILESPERPIXEL;

                if(distanceInNM < cellWidth+r )
                {
                    return true;
                }
            }
        }
    }
    return false;
}
