predict_calc (sat_t *sat, qth_t *qth, gdouble t)
{
    obs_set_t     obs_set;
    geodetic_t    sat_geodetic;
    geodetic_t    obs_geodetic;
    double        age;


    obs_geodetic.lon = qth->lon * de2ra;
    obs_geodetic.lat = qth->lat * de2ra;
    obs_geodetic.alt = qth->alt / 1000.0;
    obs_geodetic.theta = 0;

    sat->jul_utc = t;
    sat->tsince = (sat->jul_utc - sat->jul_epoch) * xmnpda;


    if (sat->flags & DEEP_SPACE_EPHEM_FLAG)
        SDP4 (sat, sat->tsince);
    else
        SGP4 (sat, sat->tsince);

    Convert_Sat_State (&sat->pos, &sat->vel);


    Magnitude (&sat->vel);
    sat->velo = sat->vel.w;
    Calculate_Obs (sat->jul_utc, &sat->pos, &sat->vel, &obs_geodetic, &obs_set);
    Calculate_LatLonAlt (sat->jul_utc, &sat->pos, &sat_geodetic);

    while (sat_geodetic.lon < -pi)
        sat_geodetic.lon += twopi;

    while (sat_geodetic.lon > (pi))
        sat_geodetic.lon -= twopi;

    sat->az = Degrees (obs_set.az);
    sat->el = Degrees (obs_set.el);
    sat->range = obs_set.range;
    sat->range_rate = obs_set.range_rate;
    sat->ssplat = Degrees (sat_geodetic.lat);
    sat->ssplon = Degrees (sat_geodetic.lon);
    sat->alt = sat_geodetic.alt;
    sat->ma = Degrees (sat->phase);
    sat->ma *= 256.0/360.0;
    sat->phase = Degrees (sat->phase);


    sat->footprint = 12756.33 * acos (xkmper / (xkmper+sat->alt));
    age = sat->jul_utc - sat->jul_epoch;
    sat->orbit = (long) floor((sat->tle.xno * xmnpda/twopi +
                    age * sat->tle.bstar * ae) * age +
                    sat->tle.xmo/twopi) + sat->tle.revnum - 1;
}
