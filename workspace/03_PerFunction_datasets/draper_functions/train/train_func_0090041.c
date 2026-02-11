ap_config_init (apconfig* ap)
{

  ap->verbose  = FALSE;
  ap->debug    = FALSE;
  ap->quiet    = FALSE;
  ap->duration = PREVIEW_DURATION;
  ap->position = START_PLAYING_ANYWHERE;
  ap->fastseek = FALSE;
  ap->no_audio = FALSE;

  ap->no_video = (!getenv ("DISPLAY") || strlen(getenv ("DISPLAY")) == 0);
  ap->entirely = FALSE;
  ap->shuffle  = FALSE;
  ap->loop     = FALSE;
  ap->colors   = "auto";
  ap->want_colors = need_colors (ap->colors);
  ap->volume   = 100;
  ap->maxduration = -1;
  ap->terminal_cols = get_terminal_width();
  ap->playlist_from_file = NULL;
  tcgetattr (STDIN_FILENO, &ap->savedttystate);
}
