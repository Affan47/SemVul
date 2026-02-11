nccf_inq_axis_type(int ncid, int varid, int *axis_type)
{
   char value[NC_MAX_NAME + 1];
   int i;
   int ret;


   if ((ret = nc_get_att_text(ncid, varid, COORDINATE_AXIS_TYPE,
				 value)))
      return ret;


   for (i = 1; i <= NCCF_RADDIST; i++)
      if (!strcmp(value, axis_type_name[i]))
	 break;


   if (i == NCCF_HEIGHT_UP)
   {
      if ((ret = nc_get_att_text(ncid, varid, COORDINATE_Z_IS_POSITIVE,
				    value)))
	 return ret;
      if (!strcmp(value, Z_DOWN))
	 i = NCCF_HEIGHT_DOWN;
   }


   if (i > NCCF_RADDIST)
      return NCCF_NOAXISTYPE;

   if (axis_type)
      *axis_type = i;

   return NC_NOERR;
}
