drawShadedRoute()
{
    int intervalTime = 60;
    double rtime=0;
    int count=0;
    int rwatts=0;
    double prevtime=0;

    QString code;

    foreach(RideFilePoint *rfp, myRideItem->ride()->dataPoints()) {

        if (count == 0) {
            code = QString("{\nvar polyline = new google.maps.Polyline();\n"
                   "   polyline.setMap(map);\n"
                   "   path = polyline.getPath();\n");
        } else {
            if (rfp->lat || rfp->lon)
                code += QString("path.push(new google.maps.LatLng(%1,%2));\n").arg(rfp->lat,0,'g',GPS_COORD_TO_STRING).arg(rfp->lon,0,'g',GPS_COORD_TO_STRING);
        }


        rtime += rfp->secs - prevtime;
        rwatts += rfp->watts;
        prevtime = rfp->secs;
        count++;


        if (rtime >= intervalTime) {

            int avgWatts = rwatts / count;
            QColor color = GetColor(avgWatts);


            count = rwatts = rtime = 0;


            code += QString("var polyOptions = {\n"
                            "    strokeColor: '%1',\n"
                            "    strokeWeight: 3,\n"
                            "    strokeOpacity: 0.5,\n"
                            "    zIndex: 0,\n"
                            "}\n"
                            "polyline.setOptions(polyOptions);\n"
                            "}\n").arg(color.name());

            view->page()->mainFrame()->evaluateJavaScript(code);
        }
    }
}
