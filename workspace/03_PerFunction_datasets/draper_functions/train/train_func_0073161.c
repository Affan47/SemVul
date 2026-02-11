Jim_KillCmd(Jim_Interp *interp, int argc, Jim_Obj *const *argv)
{
    int sig;
    long pid;
    Jim_Obj *pidObj;
    const char *signame;

    if (argc != 2 && argc != 3) {
        Jim_WrongNumArgs(interp, 1, argv, "?SIG|-0? pid");
        return JIM_ERR;
    }

    if (argc == 2) {
        signame = "SIGTERM";
        pidObj = argv[1];
    }
    else {
        signame = Jim_String(argv[1]);
        pidObj = argv[2];
    }


    if (strcmp(signame, "-0") == 0 || strcmp(signame, "0") == 0) {
        sig = 0;
    }
    else {
        sig = find_signal_by_name(interp, signame);
        if (sig < 0) {
            return JIM_ERR;
        }
    }

    if (Jim_GetLong(interp, pidObj, &pid) != JIM_OK) {
        return JIM_ERR;
    }

    if (kill(pid, sig) == 0) {
        return JIM_OK;
    }

    Jim_SetResultString(interp, "kill: Failed to deliver signal", -1);
    return JIM_ERR;
}
