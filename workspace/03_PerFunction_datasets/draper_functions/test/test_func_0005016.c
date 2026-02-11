create()
{

  if(verbose)
    cout << " f877 create \n";

  P16F874::create();

  delete_file_registers(0x20, 0x7f);
  delete_file_registers(0xa0, 0xff);
  add_file_registers(0x20, 0x7f, 0);
  add_file_registers(0xa0, 0xef, 0);
  add_file_registers(0x110, 0x11f, 0);
  add_file_registers(0x190, 0x19f, 0);
  alias_file_registers(0x70,0x7f,0x80);
  alias_file_registers(0x70,0x7f,0x100);
  alias_file_registers(0x70,0x7f,0x180);

  P16F877::create_sfr_map();


}
