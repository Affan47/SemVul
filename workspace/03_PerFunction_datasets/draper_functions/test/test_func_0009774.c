vtkSortOnTwoIds(const void *val1, const void *val2)
#endif
  {
    if (((OTPoint *)val1)->SortId2 < ((OTPoint *)val2)->SortId2)
      {
      return (-1);
      }
    else if (((OTPoint *)val1)->SortId2 > ((OTPoint *)val2)->SortId2)
      {
      return (1);
      }

    if (((OTPoint *)val1)->SortId < ((OTPoint *)val2)->SortId)
      {
      return (-1);
      }
    else if (((OTPoint *)val1)->SortId > ((OTPoint *)val2)->SortId)
      {
      return (1);
      }
    else
      {
      return (0);
      }
  }
