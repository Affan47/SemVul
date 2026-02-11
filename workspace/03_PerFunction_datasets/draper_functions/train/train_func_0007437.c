quest_write_player_data(const quest_player *pq) {
    FILE *file;
    char write[MAX_BUF], final[MAX_BUF];
    const quest_state *state;

    snprintf(final, sizeof(final), "%s/%s/%s/%s.quest", settings.localdir, settings.playerdir, pq->player_name, pq->player_name);
    snprintf(write, sizeof(write), "%s.new", final);

    file = fopen(write, "w+");
    if (!file) {
        LOG(llevError, "quest: couldn't open player quest file %s!", write);
        draw_ext_info(NDI_UNIQUE | NDI_ALL_DMS, 0, NULL, MSG_TYPE_ADMIN, MSG_TYPE_ADMIN_LOADSAVE, "File write error on server!");
        return;
    }

    state = pq->quests;

    while (state) {
        fprintf(file, "quest %s\n", state->code);
        fprintf(file, "state %d\n", state->state);
        fprintf(file, "completed %d\n", state->was_completed);
        fprintf(file, "end_quest\n");
        state = state->next;
    }

    fclose(file);

    unlink(final);
    rename(write, final);
}
