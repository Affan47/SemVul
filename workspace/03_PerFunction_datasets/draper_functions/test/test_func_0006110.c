getTrackPoint ( D304 * p)
{
    TcxTrackpoint * singlePoint = new TcxTrackpoint(GpsFunctions::print_dtime(p->time));

    if (( p->posn.lat != 0x7fffffff ) && ( p->posn.lon != 0x7fffffff )) {
        stringstream lat;
        lat.precision(10);
        stringstream lon;
        lon.precision(10);
        lat << SEMI2DEG(p->posn.lat);
        lon << SEMI2DEG(p->posn.lon);
        singlePoint->setPosition(lat.str(), lon.str());
    }

    stringstream ss;
    if (p->alt < 1.0e24 ) {
        ss << p->alt;
        singlePoint->setAltitudeMeters(ss.str());
    }
    if (p->distance < 1.0e24 ) {
        ss.str("");
        ss << p->distance;
        singlePoint->setDistanceMeters(ss.str());
    }
    if ( p->heart_rate != 0 ) {
        ss.str("");
        ss << (unsigned int)(p->heart_rate);
        singlePoint->setHeartRateBpm(ss.str());
    }
    if (this->runType == 0) {
        singlePoint->setCadenceSensorType(TrainingCenterDatabase::Bike);
    } else {
        singlePoint->setCadenceSensorType(TrainingCenterDatabase::Footpod);
    }
    if ( p->cadence != 0xff ) {
        ss.str("");
        ss << (unsigned int)(p->cadence);
        singlePoint->setCadence(ss.str());
    }
    if ( p->sensor != 0 ) {
        singlePoint->setSensorState(TrainingCenterDatabase::Present);
    } else {
        singlePoint->setSensorState(TrainingCenterDatabase::Absent);
    }

    return singlePoint;
}
