update()
{

  while (! delay) {
    u8	cmnd;
    u8	data;


    if (! decode_octet (& cmnd))
      return false;

    if (! decode_octet (& data))
      return false;


    switch (cmnd) {


    case 0xff:
      delay = 1 + (u8) (data - 1);
      break;


    default:
      opl->write (cmnd, data);

    }
  }


  if (delay)
    delay--;


  play_pos++;
  return true;
}
