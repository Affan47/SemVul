check_args(int i, int argc, char **argv) {
    if (strcmp(argv[i], "-H")==0 || strcmp(argv[i], "--tryhttp")==0) {

    } else {
        return -1;
    }

    return 0;
}
