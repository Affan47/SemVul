handle_signal(int sfd)
{
    struct signalfd_siginfo fdsi;
    EXPECT(read(sfd, &fdsi, sizeof(fdsi)) == sizeof(fdsi));

    switch (fdsi.ssi_signo) {
    case SIGINT:
        dump_all_events();


        fprintf(stderr, "Killing target process...\n");
        kill(target_pid, SIGKILL);
        break;

    case SIGCHLD: {
        int status;

        EXPECT_ERRNO(waitpid(fdsi.ssi_pid, &status, WNOHANG) > 0);
        handle_child_event(fdsi.ssi_pid, status);
    } break;


    default:
        fprintf(stderr, "Unhandled signal: %i\n", fdsi.ssi_signo);
        break;
    }
}
