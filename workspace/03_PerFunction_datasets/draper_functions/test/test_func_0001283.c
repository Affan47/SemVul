nc4_rec_grp_del(NC_GRP_INFO_T **list, NC_GRP_INFO_T *grp)
{
   NC_GRP_INFO_T *g, *c;
   NC_VAR_INFO_T *v, *var;
   NC_ATT_INFO_T *a, *att;
   NC_DIM_INFO_T *d, *dim;
   NC_TYPE_INFO_T *type, *t;
   int retval;

   assert(grp);
   LOG((3, "nc4_rec_grp_del: grp->name %s", grp->name));


   g = grp->children;
   while(g)
   {
      c = g->next;
      if ((retval = nc4_rec_grp_del(&(grp->children), g)))
         return retval;
      g = c;
   }


   att = grp->att;
   while (att)
   {
      LOG((4, "nc4_rec_grp_del: deleting att %s", att->name));
      a = att->next;
      if ((retval = nc4_att_list_del(&grp->att, att)))
         return retval;
      att = a;
   }


   var = grp->var;
   while (var)
   {
      LOG((4, "nc4_rec_grp_del: deleting var %s", var->name));


      if (var->hdf_datasetid && !var->dimscale &&
          H5Dclose(var->hdf_datasetid) < 0)
         return NC_EHDFERR;
      v = var->next;
      if ((retval = var_list_del(&grp->var, var)))
         return retval;
      var = v;
   }


   dim = grp->dim;
   while (dim)
   {
      LOG((4, "nc4_rec_grp_del: deleting dim %s", dim->name));

      if (dim->hdf_dimscaleid && H5Dclose(dim->hdf_dimscaleid) < 0)
         return NC_EHDFERR;
      d = dim->next;
      if ((retval = nc4_dim_list_del(&grp->dim, dim)))
         return retval;
      dim = d;
   }


   type = grp->type;
   while (type)
   {
      LOG((4, "nc4_rec_grp_del: deleting type %s", type->name));
      t = type->next;
      if ((retval = type_list_del(&grp->type, type)))
         return retval;
      type = t;
   }


   LOG((4, "nc4_rec_grp_del: closing group %s", grp->name));
   if (grp->hdf_grpid && H5Gclose(grp->hdf_grpid) < 0)
      return NC_EHDFERR;


   free(grp->name);


   grp_list_del(list, grp);

   return NC_NOERR;
}
