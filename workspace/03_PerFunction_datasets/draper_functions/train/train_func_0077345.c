packet_set_sequence(struct packet *packet, unsigned long opref)
{
    gw_assert(packet != NULL);

    octstr_set_char(packet->data, 0, opref & 0xff);
    octstr_set_char(packet->data, 1, (opref >> 8) & 0xff);
    octstr_set_char(packet->data, 2, (opref >> 16) & 0xff);
    octstr_set_char(packet->data, 3, (opref >> 24) & 0xff);
    packet->opref = opref;
}
