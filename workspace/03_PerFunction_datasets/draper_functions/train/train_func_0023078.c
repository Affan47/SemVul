EmailSend(Email email)
{
  FILE      *output;
  struct tm *ptm;
  char       cmd   [BUFSIZ];
  char       date  [BUFSIZ];

  fflush(email->body);
  sprintf(cmd,_PATH_SENDMAIL " %s",email->to);

  output = popen(cmd,"w");
  if (output == NULL) return errno;

  ptm = localtime(&email->timestamp);
  strftime(date,BUFSIZ,"%a, %d %b %Y %H:%M:%S %Z",ptm);

  if (!empty_string(email->replyto))
    fprintf(output,"Reply-To: <%s>\n",email->replyto);

  fprintf(
  	output,
  	"From: <%s>\n"
  	"To: <%s>\n"
  	"Subject: %s\n"
  	"Date: <%s>\n"
  	"\n"
  	"%s\n",
  	email->from,
  	email->to,
  	email->subject,
  	date,
  	email->tbody
  );

  fclose(output);
  return(0);
}
