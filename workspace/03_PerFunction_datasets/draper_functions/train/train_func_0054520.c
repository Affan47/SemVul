ieee80211_radiotap_iterator_next (struct Ieee80211RadiotapHeaderIterator *iterator)
{


  static const uint8_t rt_sizes[] = {
    [IEEE80211_RADIOTAP_TSFT] = 0x88,
    [IEEE80211_RADIOTAP_FLAGS] = 0x11,
    [IEEE80211_RADIOTAP_RATE] = 0x11,
    [IEEE80211_RADIOTAP_CHANNEL] = 0x24,
    [IEEE80211_RADIOTAP_FHSS] = 0x22,
    [IEEE80211_RADIOTAP_DBM_ANTSIGNAL] = 0x11,
    [IEEE80211_RADIOTAP_DBM_ANTNOISE] = 0x11,
    [IEEE80211_RADIOTAP_LOCK_QUALITY] = 0x22,
    [IEEE80211_RADIOTAP_TX_ATTENUATION] = 0x22,
    [IEEE80211_RADIOTAP_DB_TX_ATTENUATION] = 0x22,
    [IEEE80211_RADIOTAP_DBM_TX_POWER] = 0x11,
    [IEEE80211_RADIOTAP_ANTENNA] = 0x11,
    [IEEE80211_RADIOTAP_DB_ANTSIGNAL] = 0x11,
    [IEEE80211_RADIOTAP_DB_ANTNOISE] = 0x11,
    [IEEE80211_RADIOTAP_TX_FLAGS] = 0x22,
    [IEEE80211_RADIOTAP_RX_FLAGS] = 0x22,
    [IEEE80211_RADIOTAP_RTS_RETRIES] = 0x11,
    [IEEE80211_RADIOTAP_DATA_RETRIES] = 0x11


  };


  while (iterator->arg_index < sizeof (rt_sizes))
  {
    int hit = (0 != (iterator->bitmap_shifter & 1));

    if (hit)
    {
      unsigned int wanted_alignment;
      unsigned int unalignment;


      wanted_alignment = rt_sizes[iterator->arg_index] >> 4;
      unalignment = (((void *) iterator->arg) - ((void *) iterator->rtheader)) & (wanted_alignment - 1);
      if (0 != unalignment)
      {

	iterator->arg_index += wanted_alignment - unalignment;
      }


      iterator->this_arg_index = iterator->arg_index;
      iterator->this_arg = iterator->arg;


      iterator->arg += rt_sizes[iterator->arg_index] & 0x0f;


      if ((((void *) iterator->arg) - ((void *) iterator->rtheader)) > iterator->max_length)
	return -1;
    }


    iterator->arg_index++;

    if (0 == (iterator->arg_index % 32))
    {

      if (0 != (iterator->bitmap_shifter & 1))
      {

        iterator->bitmap_shifter = GNUNET_le32toh (*iterator->next_bitmap);
        iterator->next_bitmap++;
      }
      else
      {

        iterator->arg_index = sizeof (rt_sizes);
      }
    }
    else
    {

      iterator->bitmap_shifter >>= 1;
    }


    if (hit)
      return iterator->this_arg_index;
  }


  return -1;
}
