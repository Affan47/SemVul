handle_custom_action(int action, int state) {
    write_log("handle_custom_action %d\n", action);
    if (action >= INPUTEVENT_SPC_DISKSWAPPER_0_0 &&
            action <= INPUTEVENT_SPC_DISKSWAPPER_3_19) {
        int offset = action - INPUTEVENT_SPC_DISKSWAPPER_0_0;
        int drive = offset / AMIGA_FLOPPY_LIST_SIZE;
        int entry = offset % AMIGA_FLOPPY_LIST_SIZE;

        amiga_floppy_set_from_list(drive, entry);
        return 1;
    }


    return 0;
}
