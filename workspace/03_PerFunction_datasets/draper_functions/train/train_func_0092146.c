get_orbit_type (sat_t *sat)
{
     orbit_type_t orbit = ORBIT_TYPE_UNKNOWN;

     if (geostationary (sat)) {
          orbit = ORBIT_TYPE_GEO;
     }
     else if (decayed (sat)) {
          orbit = ORBIT_TYPE_DECAYED;
     }
     else {
          orbit = ORBIT_TYPE_UNKNOWN;
     }

     return orbit;
}
