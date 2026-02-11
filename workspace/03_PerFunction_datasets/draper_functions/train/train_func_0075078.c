ghosd_flash(Ghosd *ghosd, int fade_ms, int total_display_ms) {
  GhosdFlashData flash = {0};
  memcpy(&flash.user_render, &ghosd->render, sizeof(RenderCallback));
  ghosd_set_render(ghosd, flash_render, &flash, flash_destroy);

  ghosd_show(ghosd);

  const int STEP_MS = 50;
  const float dalpha = 1.0 / (fade_ms / (float)STEP_MS);
  struct timeval tv_nextupdate;


  for (flash.alpha = 0; flash.alpha < 1.0; flash.alpha += dalpha) {
    if (flash.alpha > 1.0) flash.alpha = 1.0;
    ghosd_render(ghosd);

    gettimeofday(&tv_nextupdate, NULL);
    tv_nextupdate.tv_usec += STEP_MS*1000;
    ghosd_main_until(ghosd, &tv_nextupdate);
  }


  flash.alpha = 1.0;
  ghosd_render(ghosd);

  gettimeofday(&tv_nextupdate, NULL);
  tv_nextupdate.tv_usec += (total_display_ms - (2*fade_ms))*1000;
  ghosd_main_until(ghosd, &tv_nextupdate);


  for (flash.alpha = 1.0; flash.alpha > 0.0; flash.alpha -= dalpha) {
    ghosd_render(ghosd);

    gettimeofday(&tv_nextupdate, NULL);
    tv_nextupdate.tv_usec += STEP_MS*1000;
    ghosd_main_until(ghosd, &tv_nextupdate);
  }

  flash.alpha = 0;
  ghosd_render(ghosd);


  gettimeofday(&tv_nextupdate, NULL);
  tv_nextupdate.tv_usec += 500*1000;
  ghosd_main_until(ghosd, &tv_nextupdate);
}
