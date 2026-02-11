get_distance_points(Point P1,Point P2,gboolean f3)
{
   gchar *distance;
   gdouble Distance;
   guint i;

   Distance = 0.0;
   for(i=0;i<3;i++)
 	Distance += (P1.C[i]- P2.C[i])*(P1.C[i]- P2.C[i]);

   Distance = sqrt(Distance)*BOHR_TO_ANG;
   if(f3)
   	distance = g_strdup_printf("%7.3lf",Distance);
   else
   	distance = g_strdup_printf("%0.20lf",Distance);
  return distance;
}
