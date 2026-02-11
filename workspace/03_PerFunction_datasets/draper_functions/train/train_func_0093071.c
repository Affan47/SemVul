nc4_rec_write_types(NC_GRP_INFO_T *grp)
{
   NC_GRP_INFO_T *child_grp;
   NC_TYPE_INFO_T *type;
   int retval;

   assert(grp && grp->name);
   LOG((3, "nc4_rec_write_types: grp->name %s", grp->name));


   if (!grp->hdf_grpid)
      if ((retval = create_group(grp)))
         return retval;


   if (!grp->parent && (grp->file->nc4_info->cmode & NC_CLASSIC_MODEL))
      if ((retval = write_nc3_strict_att(grp->hdf_grpid)))
         return retval;


   for (type = grp->type; type; type = type->next)
      if ((retval = commit_type(grp, type)))
         return retval;


   for (child_grp = grp->children; child_grp; child_grp = child_grp->next)
      if ((retval = nc4_rec_write_types(child_grp)))
         return retval;

   return NC_NOERR;
}
