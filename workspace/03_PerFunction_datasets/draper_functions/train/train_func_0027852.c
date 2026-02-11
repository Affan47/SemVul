client_tile_get_known(const struct tile *ptile)
{
  if (NULL == client.conn.playing) {
    if (client_is_observer()) {
      return TILE_KNOWN_SEEN;
    } else {
      return TILE_UNKNOWN;
    }
  }
  return tile_get_known(ptile, client.conn.playing);
}
