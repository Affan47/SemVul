shuttleVFD_flush(Driver *drvthis)
{
  PrivateData *p = drvthis->private_data;
  char packet[SHUTTLE_VFD_PACKET_SIZE];


  if (strncmp(p->last_framebuf, p->framebuf, p->width * p->height) != 0) {

    memset(packet, '\0', SHUTTLE_VFD_PACKET_SIZE);
    packet[0] = 0x11;
    packet[1] = 0x02;
    send_packet(drvthis, packet);


    memset(packet, '\0', SHUTTLE_VFD_PACKET_SIZE);
    packet[0] = 0x97;
    strncpy(&packet[1], &p->framebuf[0], 7);
    send_packet(drvthis, packet);


    memset(packet, '\0', SHUTTLE_VFD_PACKET_SIZE);
    packet[0] = 0x97;
    strncpy(&packet[1], &p->framebuf[7], 7);
    send_packet(drvthis, packet);


    memset(packet, '\0', SHUTTLE_VFD_PACKET_SIZE);
    packet[0] = 0x96;
    strncpy(&packet[1], &p->framebuf[14], 6);
    send_packet(drvthis, packet);

    strncpy(p->last_framebuf, p->framebuf, p->width * p->height);
  }


  if (p->last_icons != p->icons) {
    memset(packet, 0, SHUTTLE_VFD_PACKET_SIZE);
    packet[0] = 0x74;
    packet[1] = (p->icons >> 15) & 0x1f;
    packet[2] = (p->icons >> 10) & 0x1f;
    packet[3] = (p->icons >> 5) & 0x1f;
    packet[4] = p->icons & 0x1f;
    send_packet(drvthis, packet);

    p->last_icons = p->icons;
  }
}
