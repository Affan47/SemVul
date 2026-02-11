ask_user_filename(const char *prompt, char *buffer, size_t length,
                              VBOOL require_existance)
{
  ask_user(prompt, buffer, length, TRUE, FALSE);
  if (require_existance)
    {
      FILE *fp;
      fp = fopen(buffer, "rb");
      while (fp == NULL)
        {
	  alert_user("Cannot open %s: %s", buffer, strerror(errno));
          ask_user(prompt, buffer, length, TRUE, FALSE);
          fp = fopen(buffer, "rb");
	}
      fclose(fp);
    }
}
