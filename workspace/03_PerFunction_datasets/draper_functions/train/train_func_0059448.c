real_perform_child( daemonCtrl &daemon_ctrl, char *argv[] )
{

    close_log();

    try {
        daemon_ctrl.cmd_attach();

        execvp(argv[0], argv);

        perror("Fakeroot-ng exec failed");
    } catch( const errno_exception &exception ) {
        fprintf(stderr, "%s: %s\n", exception.what(), exception.get_error_message() );
    } catch( const std::exception &exception ) {
        fprintf(stderr, "Fatal error: %s\n", exception.what() );
    }

    return 2;
}
