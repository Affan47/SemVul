stop() {
    if(dumper_thread_state == FRAME_EXPORTER_STOPPED || dumper_thread_state == FRAME_EXPORTER_EXIT) return;

    SDL_mutexP(mutex);

        dumper_thread_state = FRAME_EXPORTER_EXIT;

        SDL_CondSignal(cond);

    SDL_mutexV(mutex);


    while(dumper_thread_state != FRAME_EXPORTER_STOPPED)
        SDL_Delay(100);
}
