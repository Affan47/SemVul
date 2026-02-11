load_pin_juyin()
{
  text_pho_N = 6;
  char pinfname[128];

  get_sys_table_file_name("pin-juyin.xlt", pinfname);


  FILE *fr;
  if ((fr=fopen(pinfname,"rb"))==NULL)
     p_err("Cannot open %s", pinfname);

  fread(&pin_juyinN, sizeof(short), 1, fr);
  pin_juyin = tmalloc(PIN_JUYIN, pin_juyinN);
  fread(pin_juyin, sizeof(PIN_JUYIN), pin_juyinN, fr);
  fclose(fr);
}
