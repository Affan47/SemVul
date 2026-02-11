wsh_loop() {

    enum WSH_STATUS status = OK;

    signal_handler();

    do {

        printf("%s> ", my_platform.cwd);

        wsh_input input = wsh_readln();
        if (input.length <= 0) {
            clear_input(&input);
            continue;
        }

        wsh_command cmd = wsh_parseln(&input);
        clear_input(&input);

        if (cmd.nargs <= 0) {
            clear_command(&cmd);
            continue;
        }

        status = wsh_execute(&cmd);
        clear_command(&cmd);

    } while (OK == status || APPLICATION_FAILURE == status);

    return status;

}
