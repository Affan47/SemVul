DBMathGuessProjection (DBRegion extent)
   {
   if (extent.LowerLeft.X < -180.0) return (DBProjectionCartesian);
   if (extent.LowerLeft.Y < - 90.0) return (DBProjectionCartesian);
   if (extent.UpperRight.X > 180.0) return (DBProjectionCartesian);
   if (extent.UpperRight.Y >  90.0) return (DBProjectionCartesian);
   return (DBProjectionSpherical);
   }
