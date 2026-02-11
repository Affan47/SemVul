input_run(int id)
{
    cams[id].pglobal->in[id].buf = malloc(cams[id].videoIn->framesizeIn);
    if(cams[id].pglobal->in[id].buf == NULL) {
        fprintf(stderr, "could not allocate memory\n");
        exit(EXIT_FAILURE);
    }

    DBG("launching camera thread #%02d\n", id);

    pthread_create(&(cams[id].threadID), NULL, cam_thread, &(cams[id]));
    pthread_detach(cams[id].threadID);
    return 0;
}
