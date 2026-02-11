GRIupdateRIG(int32 hdf_file_id,ri_info_t *img_ptr)
{
    CONSTR(FUNC, "GRIupdateRIG");
    int32 GroupID;
    intn   ret_value = SUCCEED;

    HEclear();
    if (!HDvalidfid(hdf_file_id) || img_ptr==NULL)
        HGOTO_ERROR(DFE_ARGS, FAIL);


    if(img_ptr->img_dim.nt!=DFNT_UINT8 || (img_ptr->img_dim.ncomps!=1
            && img_ptr->img_dim.ncomps!=3))
      {
        ret_value =(SUCCEED);
        goto done;
      }


    if (GRIupdatemeta(hdf_file_id,img_ptr)==FAIL)
        HGOTO_ERROR(DFE_INTERNAL, FAIL);


    if ((GroupID = DFdisetup(6)) == FAIL)
        HGOTO_ERROR(DFE_GROUPSETUP, FAIL);


    if (DFdiput(GroupID, DFTAG_ID, (uint16) img_ptr->img_dim.dim_ref) == FAIL)
        HGOTO_ERROR(DFE_PUTGROUP, FAIL);


    if (DFdiput(GroupID, img_ptr->img_tag, img_ptr->img_ref) == FAIL)
        HGOTO_ERROR(DFE_PUTGROUP, FAIL);


    if(img_ptr->lut_ref!=DFREF_WILDCARD)
      {

          if (DFdiput(GroupID, DFTAG_LD, (uint16) img_ptr->lut_dim.dim_ref) == FAIL)
              HGOTO_ERROR(DFE_PUTGROUP, FAIL);


          if (DFdiput(GroupID, img_ptr->lut_tag, img_ptr->lut_ref) == FAIL)
              HGOTO_ERROR(DFE_PUTGROUP, FAIL);
      }


    if(img_ptr->rig_ref==DFTAG_WILDCARD)
        img_ptr->rig_ref=Htagnewref(hdf_file_id,DFTAG_RIG);
    if(DFdiwrite(hdf_file_id, GroupID, DFTAG_RIG, img_ptr->rig_ref)==FAIL)
        HGOTO_ERROR(DFE_GROUPWRITE, FAIL);

done:
  if(ret_value == FAIL)
    {

    }


  return ret_value;
}
