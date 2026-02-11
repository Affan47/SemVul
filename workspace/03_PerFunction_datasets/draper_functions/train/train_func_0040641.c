calculate_difblock_location (guint8 * block)
{
  gint block_type, dif_sequence, dif_block;
  guint location;

  block_type = block[0] >> 5;
  dif_sequence = block[1] >> 4;
  dif_block = block[2];

  location = dif_sequence * 150;

  switch (block_type) {
    case 0:
      break;
    case 1:
      location += (1 + dif_block);
      break;
    case 2:
      location += (3 + dif_block);
      break;
    case 3:
      location += (6 + dif_block * 16);
      break;
    case 4:
      location += (7 + (dif_block / 15) + dif_block);
      break;
    default:
      GST_DEBUG ("UNKNOWN BLOCK");
      location = -1;
      break;
  }
  return location;
}
