attach_item(struct linked_server *ls,
            struct item *item)
{
    struct world *world = &ls->connection->client.world;

    item->attach_sequence = world->item_attach_sequence;

    if (item->packet_container_update.cmd == PCK_ContainerUpdate) {

        uint32_t parent_serial
            = item->packet_container_update.item.parent_serial;
        struct item *parent = world_find_item(world, parent_serial);
        if (parent != NULL &&
            parent->attach_sequence != world->item_attach_sequence)
            attach_item(ls, parent);


        if (ls->client_version.protocol < PROTOCOL_6) {

            struct uo_packet_container_update p5;

            container_update_6_to_5(&p5, &item->packet_container_update);
            uo_server_send(ls->server, &p5, sizeof(p5));
        } else {
            uo_server_send(ls->server, &item->packet_container_update,
                           sizeof(item->packet_container_update));
        }
    }

    if (item->packet_container_open.cmd == PCK_ContainerOpen)
        uo_server_send(ls->server, &item->packet_container_open,
                       sizeof(item->packet_container_open));

    if (item->packet_world_item.cmd == PCK_WorldItem)
        uo_server_send(ls->server, &item->packet_world_item,
                       ntohs(item->packet_world_item.length));
    if (item->packet_equip.cmd == PCK_Equip)
        uo_server_send(ls->server, &item->packet_equip,
                       sizeof(item->packet_equip));
}
