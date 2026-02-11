get_date(){
    char* date = malloc(512);

    int child_pipe[2];

    pipe(child_pipe);

    int pid = fork();
    if (!pid){
        close(0);
        close(1);
        close(2);
        dup2(child_pipe[1], 1);
        char* args[] = {"-R", NULL};
        execv("/bin/date", args);
    }

    read(child_pipe[0], date, 512);
    close(child_pipe[0]);
    close(child_pipe[1]);

    return date;
}
