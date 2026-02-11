handle_player_attribute_chunk
    (const struct packet_player_attribute_chunk *packet)
{
  if (!client_has_player()) {
    return;
  }

  generic_handle_player_attribute_chunk(client_player(), packet);

  if (packet->offset + packet->chunk_length == packet->total_length) {


      attribute_restore();
  }
}
