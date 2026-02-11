text_tag_initv(struct text_tag *ptag, enum text_tag_type type,
                           ft_offset_t start_offset, ft_offset_t stop_offset,
                           va_list args)
{
  ptag->type = type;
  ptag->start_offset = start_offset;
  ptag->stop_offset = stop_offset;

  switch (type) {
  case TTT_BOLD:
  case TTT_ITALIC:
  case TTT_STRIKE:
  case TTT_UNDERLINE:
    return TRUE;
  case TTT_COLOR:
    {
      struct ft_color color = va_arg(args, struct ft_color);

      if ((NULL == color.foreground || '\0' == color.foreground[0])
          && (NULL == color.background || '\0' == color.background[0])) {
        return FALSE;
      }

      if (NULL != color.foreground && '\0' != color.foreground[0]) {
        sz_strlcpy(ptag->color.foreground, color.foreground);
      } else {
        ptag->color.foreground[0] = '\0';
      }

      if (NULL != color.background && '\0' != color.background[0]) {
        sz_strlcpy(ptag->color.background, color.background);
      } else {
        ptag->color.background[0] = '\0';
      }
    }
    return TRUE;
  case TTT_LINK:
    {
      ptag->link.type = va_arg(args, enum text_link_type);
      switch (ptag->link.type) {
      case TLT_CITY:
        {
          struct city *pcity = va_arg(args, struct city *);

          if (!pcity) {
            return FALSE;
          }
          ptag->link.id = pcity->id;
          sz_strlcpy(ptag->link.name, city_name(pcity));
        }
        return TRUE;
      case TLT_TILE:
        {
          struct tile *ptile = va_arg(args, struct tile *);

          if (!ptile) {
            return FALSE;
          }
          ptag->link.id = tile_index(ptile);
          fc_snprintf(ptag->link.name, sizeof(ptag->link.name),
                      "(%d, %d)", TILE_XY(ptile));
        }
        return TRUE;
      case TLT_UNIT:
        {
          struct unit *punit = va_arg(args, struct unit *);

          if (!punit) {
            return FALSE;
          }
          ptag->link.id = punit->id;
          sz_strlcpy(ptag->link.name, unit_rule_name(punit));
        }
        return TRUE;
      };
    }
  };
  return FALSE;
}
