request_password (const char *prompt)
{
        char           buf [255];
        char          *pass;
        char          *password;
        struct termios ts0;
        struct termios ts1;

        tcgetattr (fileno (stdin), &ts0);
        ts1 = ts0;
        ts1.c_lflag &= ~ECHO;

        printf ("%s", prompt);

        if (tcsetattr (fileno (stdin), TCSAFLUSH, &ts1) != 0) {
                fprintf (stderr, "Could not set terminal attributes\n");
                exit (1);
        }

        pass = fgets (buf, sizeof (buf) - 1, stdin);

        tcsetattr (fileno (stdin), TCSANOW, &ts0);

        if (!pass || !*pass) {
                exit (0);
        }

        if (pass [strlen (pass) - 1] == '\n') {
                pass [strlen (pass) - 1] = 0;
        }

        password = g_strdup (pass);

        memset (pass, '\b', strlen (pass));

        return password;
}
