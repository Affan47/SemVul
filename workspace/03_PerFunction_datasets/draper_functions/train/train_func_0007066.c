net80211_check_settings_update ( void )
{
	struct net80211_device *dev;
	char ssid[IEEE80211_MAX_SSID_LEN + 1];
	int key_reassoc;

	list_for_each_entry ( dev, &net80211_devices, list ) {
		if ( ! ( dev->netdev->state & NETDEV_OPEN ) )
			continue;

		key_reassoc = 0;
		if ( dev->handshaker && dev->handshaker->change_key &&
		     dev->handshaker->change_key ( dev ) < 0 )
			key_reassoc = 1;

		fetch_string_setting ( netdev_settings ( dev->netdev ),
				       &net80211_ssid_setting, ssid,
				       IEEE80211_MAX_SSID_LEN + 1 );

		if ( key_reassoc ||
		     ( ! ( ! ssid[0] && ( dev->state & NET80211_AUTO_SSID ) ) &&
		       strcmp ( ssid, dev->essid ) != 0 ) ) {
			DBGC ( dev, "802.11 %p updating association: "
			       "%s -> %s\n", dev, dev->essid, ssid );
			net80211_autoassociate ( dev );
		}
	}

	return 0;
}
