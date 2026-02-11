info(int all, int longout, int group, int label)
{
    int         idx;
    int         empty = 0;
    int         start, end;
    int         d;
    int        *mark;
    int i, j;

    if (!fileOpen())
      {
          noFile();
          return HE_OK;
      }

    if (!group || (!isGrp(currTag) && !all))
      {
          if (all)
            {
                start = 0;
                end = he_numDesc - 1;
            }
          else
              start = end = he_currDesc;

          for (i = start; i <= end; i++)
              if (he_desc[i].tag == DFTAG_NULL)
                  empty++;
              else
                {
                    if (all && i == he_currDesc)
                        printf("*");
                    else
                        printf(" ");
                    printf("(%d) ", i + 1);
                    infoDesc(i, longout, label);
                }

          if (empty > 0)
              printf("Empty (tag %d) : %d slots.\n", DFTAG_NULL, empty);
      }
    else
      {
          mark = (int *) HDcalloc(he_numDesc, sizeof(int));

          if (all)
            {
                start = 0;
                end = he_numGrp - 1;
            }
          else
            {
                if (he_numGrp == 0)
                  {
                      fprintf(stderr, "There is no group in this file.\n");
                      return HE_FAIL;
                  }
                start = end = currGrpNo;
            }
          for (i = start; i <= end; i++)
            {
                printf("**Group %d:\n", i + 1);
                idx = he_grp[i].desc;
                infoDesc(idx, longout, label);

                mark[idx] = YES;

                for (j = 0; j < he_grp[i].size; j++)
                    if ((d = findDesc(he_grp[i].ddList + j)) >= 0)
                      {
                          mark[d] = 1;
                          infoDesc(d, longout, 0);
                      }
                    else
                        fprintf(stderr,
                            "**Tag: %d, Ref: %d not in descriptors list!\n",
                                he_grp[i].ddList[j].tag,
                                he_grp[i].ddList[j].ref);
            }
          if (all)
            {
                puts("\n**These do not belong to any group:");
                for (i = 0; i < he_numDesc; i++)
                    if (!mark[i]) {
                        if (he_desc[i].tag == DFTAG_NULL)
                            empty++;
                        else
                            infoDesc(i, longout, label);
                    }

                if (empty > 0)
                    printf("Empty (tag %d) : %d slots.\n", DFTAG_NULL, empty);
            }
      }
    return HE_OK;
}
