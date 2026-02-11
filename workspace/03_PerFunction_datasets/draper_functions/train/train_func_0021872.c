imap_unseen_command(struct mail_s *mail, unsigned long old_unseen, unsigned long old_messages)
{
	if (strlen(mail->command) > 1 && (mail->unseen > old_unseen
				|| (mail->messages > old_messages && mail->unseen > 0))) {

		if (system(mail->command) == -1) {
			perror("system()");
		}
	}
}
