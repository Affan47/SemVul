ieee80211_radiotap_iterator_init (struct Ieee80211RadiotapHeaderIterator *iterator,
                                  const struct Ieee80211RadiotapHeader *radiotap_header,
				  size_t max_length)
{
  if ( (iterator == NULL) ||
       (radiotap_header == NULL) )
    return -1;


  if (0 != radiotap_header->it_version)
    return -1;


  if ( (max_length < sizeof (struct Ieee80211RadiotapHeader)) ||
       (max_length < (GNUNET_le16toh (radiotap_header->it_len))) )
    return -1;

  memset (iterator, 0, sizeof (struct Ieee80211RadiotapHeaderIterator));
  iterator->rtheader = radiotap_header;
  iterator->max_length = GNUNET_le16toh (radiotap_header->it_len);
  iterator->bitmap_shifter = GNUNET_le32toh (radiotap_header->it_present);
  iterator->arg = ((uint8_t *) radiotap_header) + sizeof (struct Ieee80211RadiotapHeader);


  if (0 != (iterator->bitmap_shifter & IEEE80211_RADIOTAP_PRESENT_EXTEND_MASK))
  {
    while (GNUNET_le32toh (*((uint32_t *) iterator->arg)) & IEEE80211_RADIOTAP_PRESENT_EXTEND_MASK)
    {
      iterator->arg += sizeof (uint32_t);


      if (iterator->arg - ((uint8_t*) iterator->rtheader) > iterator->max_length)
        return -1;
    }
    iterator->arg += sizeof (uint32_t);


  }

  return 0;
}
