utminvint(
double r_maj,
double r_min,
double scale_fact,
long zone)
{
double temp;

if ((labs(zone) < 1) || (labs(zone) > 60))
   {
   p_error("Illegal zone number","utm-invint");
   return(11);
   }
r_major = r_maj;
r_minor = r_min;
scale_factor = scale_fact;
lat_origin = 0.0;
lon_center = ((6 * labs(zone)) - 183) * D2R;
false_easting = 500000.0;
false_northing = (zone < 0) ? 10000000.0 : 0.0;

temp = r_minor / r_major;
es = 1.0 - SQUARE(temp);
e0 = e0fn(es);
e1 = e1fn(es);
e2 = e2fn(es);
e3 = e3fn(es);
ml0 = r_major * mlfn(e0, e1, e2, e3, lat_origin);
esp = es / (1.0 - es);

if (es < .00001)
   ind = 1;
else
   ind = 0;


ptitle("UNIVERSAL TRANSVERSE MERCATOR (UTM)");
genrpt_long(zone,   "Zone:     ");
radius2(r_major, r_minor);
genrpt(scale_factor,"Scale Factor at C. Meridian:     ");
cenlonmer(lon_center);
return(OK);
}
