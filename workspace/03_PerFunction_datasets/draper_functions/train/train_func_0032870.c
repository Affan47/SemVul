ssdv_dec_header(ssdv_packet_info_t *info, uint8_t *packet)
{
	info->callsign  = (packet[2] << 24) | (packet[3] << 16) | (packet[4] << 8) | packet[5];
	info->image_id   = packet[6];
	info->packet_id  = (packet[7] << 8) | packet[8];
	info->width      = packet[9] << 4;
	info->height     = packet[10] << 4;
	info->mcu_mode   = packet[11] & 0x03;
	info->mcu_offset = packet[12];
	info->mcu_id     = (packet[13] << 8) | packet[14];
	info->mcu_count  = packet[9] * packet[10];
	if(info->mcu_mode == 1 || info->mcu_mode == 2) info->mcu_count *= 2;
	else if(info->mcu_mode == 3) info->mcu_count *= 4;
}
