GRwritelut(int32 lutid,int32 ncomps,int32 nt,int32 il,int32 nentries,void * data)
{
    CONSTR(FUNC, "GRwritelut");
    int32 hdf_file_id;
    ri_info_t *ri_ptr;
    intn  ret_value = SUCCEED;


    HEclear();


    if (HAatom_group(lutid)!=RIIDGROUP || ncomps<1 || (DFKNTsize(nt)==FAIL)
            || nentries<1 || data==NULL)
        HGOTO_ERROR(DFE_ARGS, FAIL);


    if (NULL == (ri_ptr = (ri_info_t *) HAatom_object(lutid)))
        HGOTO_ERROR(DFE_LUTNOTFOUND, FAIL);
    hdf_file_id=ri_ptr->gr_ptr->hdf_file_id;


    if(ncomps==3 && (nt==DFNT_UINT8 ||nt==DFNT_UCHAR8) &&
        il==MFGR_INTERLACE_PIXEL && nentries==256)
      {

          if(ri_ptr->lut_tag!=DFTAG_NULL && ri_ptr->lut_ref!=DFREF_WILDCARD)
            {
                if(Hputelement(hdf_file_id,ri_ptr->lut_tag,ri_ptr->lut_ref,
                        data,ncomps*nentries*DFKNTsize(nt))==FAIL)
                    HGOTO_ERROR(DFE_PUTELEM,FAIL);
            }
          else
            {
                ri_ptr->lut_tag=DFTAG_LUT;
                ri_ptr->lut_ref=Htagnewref(hdf_file_id,ri_ptr->lut_tag);
                ri_ptr->lut_dim.dim_ref=DFREF_WILDCARD;
                ri_ptr->lut_dim.xdim=256;
                ri_ptr->lut_dim.ydim=1;
                ri_ptr->lut_dim.ncomps=3;
                ri_ptr->lut_dim.nt=DFNT_UINT8;
                ri_ptr->lut_dim.file_nt_subclass=DFNTF_HDFDEFAULT;
                ri_ptr->lut_dim.il=MFGR_INTERLACE_PIXEL;
                ri_ptr->lut_dim.nt_tag=DFTAG_NULL;
                ri_ptr->lut_dim.nt_ref=DFREF_WILDCARD;
                ri_ptr->lut_dim.comp_tag=DFTAG_NULL;
                ri_ptr->lut_dim.comp_ref=DFREF_WILDCARD;
                if(Hputelement(hdf_file_id,ri_ptr->lut_tag,ri_ptr->lut_ref,
                        data,ncomps*nentries*DFKNTsize(nt))==FAIL)
                    HGOTO_ERROR(DFE_PUTELEM,FAIL);

                ri_ptr->meta_modified=TRUE;
                ri_ptr->gr_ptr->gr_modified=TRUE;
            }
      }
    else
      {
          HGOTO_ERROR(DFE_UNSUPPORTED,FAIL);
      }

done:
  if(ret_value == 0)
    {

    }


  return ret_value;
}
