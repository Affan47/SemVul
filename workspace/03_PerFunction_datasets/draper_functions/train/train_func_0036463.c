set_header(glui32 width, glui32 height)
{
  unsigned i;
  zword flags[3];
  flags[1] = LOBYTE(HD_FLAGS1);
  flags[2] = LOWORD(HD_FLAGS2);

  cur_cap[DO_TANDY] = do_tandy;

  cur_cap[IS_TRANS] = is_transcripting();
  cur_cap[FORCE_FIXED] = is_fixed;

  for(i = 0; i < sizeof(z_cap_table) / sizeof(*z_cap_table); i++) {
    if(zversion >= z_cap_table[i].min_zversion
       && zversion <= z_cap_table[i].max_zversion) {
      if(cur_cap[z_cap_table[i].c])
	flags[z_cap_table[i].flagnum] |= 1 << z_cap_table[i].bit;
      else
	flags[z_cap_table[i].flagnum] &= ~(1 << z_cap_table[i].bit);
    }
  }

  LOBYTEwrite(HD_FLAGS1, flags[1]);
  LOWORDwrite(HD_FLAGS2, flags[2]);

  LOBYTEwrite(HD_TERPNUM, interp_num);
  LOBYTEwrite(HD_TERPVER, interp_ver);


  if(username)
    for(i = 0; i < 8 && username[i] && !LOBYTE(HD_USERID + i); i++)
      LOBYTEwrite(HD_USERID + i, username[i]);

  if(zversion == 6) {
    width = 320;
    height = 200;
  }


  if(height > 255)
    height = 255;
  LOBYTEwrite(HD_SCR_HEIGHT, height);
  LOBYTEwrite(HD_SCR_WIDTH, width);
  if(zversion >= 5) {
    LOWORDwrite(HD_SCR_WUNIT, width);
    LOWORDwrite(HD_SCR_HUNIT, height);
  }

  if(zversion != 6) {
    LOBYTEwrite(HD_FNT_WIDTH, 1);
    LOBYTEwrite(HD_FNT_HEIGHT, 1);
  } else {
    LOBYTEwrite(HD_FNT_WIDTH, 8);
    LOBYTEwrite(HD_FNT_HEIGHT, 8);
  }

  LOBYTEwrite(HD_DEF_BACK, 1);
  LOBYTEwrite(HD_DEF_FORE, 1);


  LOBYTEwrite(HD_STD_REV, 1);
  LOBYTEwrite(HD_STD_REV + 1, 0);
}
