HLPread(accrec_t *access_rec,
        int32     length,
        void *     datap)
{
    CONSTR(FUNC, "HLPread");
    uint8      *data = (uint8 *) datap;

    linkinfo_t *info = (linkinfo_t *) (access_rec->special_info);
    link_t     *t_link = info->link;


    int32       relative_posn = access_rec->posn;

    int32       block_idx;
    int32       current_length;
    int32       nbytes = 0;
    int32       bytes_read = 0;
    int32       ret_value = SUCCEED;


    if (length == 0)
        length = info->length - access_rec->posn;
    else
        if (length < 0)
            HGOTO_ERROR(DFE_RANGE, FAIL);

    if (access_rec->posn + length > info->length)
        length = info->length - access_rec->posn;


    if (relative_posn < info->first_length)
      {
          block_idx = 0;
          current_length = info->first_length;
      }
    else
      {
          relative_posn -= info->first_length;
          block_idx = relative_posn / info->block_length + 1;
          relative_posn %= info->block_length;
          current_length = info->block_length;
      }


    {
        int32 i;

        for (i = 0; i < block_idx / info->number_blocks; i++)
          {
              if (t_link == NULL)
                  HGOTO_ERROR(DFE_INTERNAL, FAIL);
              t_link = t_link->next;
          }
    }
    block_idx %= info->number_blocks;


    do
      {
          int32 remaining =
              current_length - relative_posn;


          if (remaining > length)
              remaining = length;
          if (t_link->block_list[block_idx].ref != 0)
            {
                int32       access_id;
                block_t    *current_block =
                    &(t_link->block_list[block_idx]);

                access_id = Hstartread(access_rec->file_id, DFTAG_LINKED,
                                       current_block->ref);
                if (access_id == (int32) FAIL
                    || (relative_posn
                && (int32) FAIL == Hseek(access_id, relative_posn, DF_START))
                    || (int32) FAIL == (nbytes = Hread(access_id, remaining, data)))
                    HGOTO_ERROR(DFE_READERROR, FAIL);

                bytes_read += nbytes;
                Hendaccess(access_id);
            }
          else
            {
                HDmemset(data, 0, (size_t)remaining);
                bytes_read += nbytes;
            }


          data += remaining;
          length -= remaining;
          if (length > 0 && ++block_idx >= info->number_blocks)
            {
                block_idx = 0;
                t_link = t_link->next;
                if (t_link == NULL)
                    HGOTO_ERROR(DFE_INTERNAL, FAIL);
            }
          relative_posn = 0;
          current_length = info->block_length;
      }
    while (length > 0);

    access_rec->posn += bytes_read;
    ret_value = bytes_read;

done:
  if(ret_value == FAIL)
    {

    }


  return ret_value;
}
