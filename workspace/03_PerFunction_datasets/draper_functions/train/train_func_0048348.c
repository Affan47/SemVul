rideSelected()
{
    RideItem *ride = myRideItem;

    if (ride == NULL) current = NULL;


    if (!amVisible()) {
        stale = true;
        setupStack = false;
        return;
    }


    if (!ride || !ride->ride() || !ride->ride()->dataPoints().count()) {
        current = NULL;
        setIsBlank(true);
        return;
    }
    else
        setIsBlank(false);


    if (ride == current && stale == false) return;


    current = ride;


    clearSelection();


    setAllPlotWidgets(ride);


    fullPlot->setDataFromRide(ride);


    int startidx, stopidx;
    if ( fullPlot->bydist == true ) {
        startidx = ride->ride()->distanceIndex( ( double ) spanSlider->lowerValue() / 1000.0 );
        stopidx = ride->ride()->distanceIndex( ( double ) spanSlider->upperValue() / 1000.0 );
    } else {
        startidx = ride->ride()->timeIndex( spanSlider->lowerValue() );
        stopidx = ride->ride()->timeIndex( spanSlider->upperValue() );
    }
    allPlot->setDataFromPlot( fullPlot, startidx, stopidx );


    redrawFullPlot();
    redrawAllPlot();


    setupStack = false;
    setupStackPlots();

    stale = false;
}
