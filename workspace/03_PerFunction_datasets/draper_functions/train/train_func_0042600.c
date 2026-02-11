nccf_parse_coords(int ncid, int varid, char *att_name, int *naxes,
		  int *axis_varids)
{
   size_t len;
   char *coords_str;
   char axis_name[NC_MAX_NAME + 1], *p, *a;
   int num_axes = 0, axes[NC_MAX_DIMS];
   int a1, ret;


   if (!att_name || strlen(att_name) > NC_MAX_NAME)
      return CF_EINVAL;


   if ((ret = nc_inq_att(ncid, varid, att_name, NULL, &len)))
      return ret;


   if (!(coords_str = malloc(len)))
      return CF_ENOMEM;


   ret = nc_get_att_text(ncid, varid, att_name, coords_str);


   for (p = coords_str; !ret && (p - coords_str) < strlen(coords_str);)
   {
      for (a = axis_name; *p && *p != ' '; )
	 *a++ = *p++;
      p++;
      *a = '\0';

      ret = nc_inq_varid(ncid, axis_name, &axes[num_axes++]);
   }


   free(coords_str);


   if (naxes)
      *naxes = num_axes;
   if (axis_varids)
      for (a1 = 0; a1 < num_axes; a1++)
	 axis_varids[a1] = axes[a1];

   return CF_NOERR;
}
