mac_test (const struct GNUNET_TRANSPORT_WLAN_Ieee80211Frame *taIeeeHeader,
          const struct HardwareInfos *dev)
{
  if (0 != memcmp (&taIeeeHeader->addr3, &mac_bssid_gnunet, MAC_ADDR_SIZE))
    return 1;
  if ( (0 == memcmp (&taIeeeHeader->addr1, &dev->pl_mac, MAC_ADDR_SIZE)) ||
       (0 == memcmp (&taIeeeHeader->addr1, &bc_all_mac, MAC_ADDR_SIZE)) )
    return 0;
  return 1;
}
