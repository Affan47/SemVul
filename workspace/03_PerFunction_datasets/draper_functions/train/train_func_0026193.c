set_chip_model(chip_model model)
{
  if (model == MOS6581) {


    mixer_DC = -0xfff*0xff/18 >> 7;

    f0 = f0_6581;
    f0_points = f0_points_6581;
    f0_count = sizeof(f0_points_6581)/sizeof(*f0_points_6581);
  }
  else {

    mixer_DC = 0;

    f0 = f0_8580;
    f0_points = f0_points_8580;
    f0_count = sizeof(f0_points_8580)/sizeof(*f0_points_8580);
  }

  set_w0();
  set_Q();
}
