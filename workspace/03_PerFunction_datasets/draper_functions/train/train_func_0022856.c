convert_k_to_rgb (gfloat  temperature,
                  gfloat *rgb)
{
  gint channel;

  if (temperature < LOWEST_TEMPERATURE)
    temperature = LOWEST_TEMPERATURE;

  if (temperature > HIGHEST_TEMPERATURE)
    temperature = HIGHEST_TEMPERATURE;


  for (channel = 0; channel < 3; channel++)
    {
      gfloat nomin, denom;
      gint   deg;

      nomin = rgb_r55[channel][0];
      for (deg = 1; deg < 6; deg++)
        nomin = nomin * temperature + rgb_r55[channel][deg];

      denom = rgb_r55[channel][6];
      for (deg = 1; deg < 6; deg++)
        denom = denom * temperature + rgb_r55[channel][6 + deg];

      rgb[channel] = nomin / denom;
    }
}
