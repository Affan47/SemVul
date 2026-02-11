kill_unmarshal(struct kill *tmp,  struct evbuffer *evbuf)
{
  ev_uint32_t tag;
  while (evbuffer_get_length(evbuf) > 0) {
    if (evtag_peek(evbuf, &tag) == -1)
      return (-1);
    switch (tag) {

      case KILL_WEAPON:

        if (tmp->weapon_set)
          return (-1);
        if (evtag_unmarshal_string(evbuf, KILL_WEAPON, &tmp->weapon_data) == -1) {
          event_warnx("%s: failed to unmarshal weapon", __func__);
          return (-1);
        }
        tmp->weapon_set = 1;
        break;

      case KILL_ACTION:

        if (tmp->action_set)
          return (-1);
        if (evtag_unmarshal_string(evbuf, KILL_ACTION, &tmp->action_data) == -1) {
          event_warnx("%s: failed to unmarshal action", __func__);
          return (-1);
        }
        tmp->action_set = 1;
        break;

      case KILL_HOW_OFTEN:

        if (tmp->how_often_length >= tmp->how_often_num_allocated &&
            kill_how_often_expand_to_hold_more(tmp) < 0) {
          puts("HEY NOW");
          return (-1);
        }
        if (evtag_unmarshal_int(evbuf, KILL_HOW_OFTEN, &tmp->how_often_data[tmp->how_often_length]) == -1) {
          event_warnx("%s: failed to unmarshal how_often", __func__);
          return (-1);
        }
        ++tmp->how_often_length;
        tmp->how_often_set = 1;
        break;

      default:
        return -1;
    }
  }

  if (kill_complete(tmp) == -1)
    return (-1);
  return (0);
}
