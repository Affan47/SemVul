p_merge_fmac_list(FMacElem *fmac_root, const char *filtermacro_file, GimpRunMode run_mode)
{
  gchar   *l_msg;
  GapValTextFileLines *txf_ptr;
  GapValTextFileLines *txf_ptr_root;

  if(gap_debug)
  {
    printf("p_merge_fmac_list:  fmac_root:%d filtermacro_file:%s\n"
           ,(int)fmac_root
           ,filtermacro_file
           );
  }

  if (!gap_fmac_chk_filtermacro_file(filtermacro_file))
  {
      l_msg = g_strdup_printf(_("file: %s is not a filtermacro file !")
                             , filtermacro_file);
      p_print_and_free_msg(l_msg, run_mode);
      return (FALSE);
  }


  txf_ptr_root = gap_val_load_textfile(filtermacro_file);
  for(txf_ptr = txf_ptr_root; txf_ptr != NULL; txf_ptr = (GapValTextFileLines *) txf_ptr->next)
  {
    FMacLine *fmacLine;

    fmacLine = p_scan_fmac_line(txf_ptr, run_mode, filtermacro_file);
    if (fmacLine)
    {
      FMacElem *fmac_elem;

      for(fmac_elem = fmac_root; fmac_elem != NULL; fmac_elem = (FMacElem *)fmac_elem->next)
      {
        if((strcmp(fmac_elem->filtername, fmacLine->filtername) == 0)
        && (fmac_elem->assigned_flag == FALSE))
        {
          if (fmac_elem->buffer_from_length == fmacLine->paramlength)
          {

            memcpy(fmac_elem->buffer_to, fmacLine->paramdata, fmacLine->paramlength);
            fmac_elem->assigned_flag = TRUE;

            if(fmac_elem->iteratorname != NULL)
            {
              fmac_elem->varying_flag = TRUE;
            }

          }
          else
          {
            printf("ERROR: parmlength %d does not match %d for filter:%s\n"
                ,(int)fmacLine->paramlength
                ,(int)fmac_elem->buffer_from_length
                ,fmacLine->filtername
                );
          }
          break;
        }
      }
      p_free_fmac_line(fmacLine);

    }
  }

  if(txf_ptr_root)
  {
    gap_val_free_textfile_lines(txf_ptr_root);
  }

  return (TRUE);
}
