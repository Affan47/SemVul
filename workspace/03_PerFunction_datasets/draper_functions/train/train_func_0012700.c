free_dialog_information(object *op) {
    struct_dialog_message *current, *next;
    struct_dialog_reply *currep, *nextrep;

    if (!QUERY_FLAG(op, FLAG_DIALOG_PARSED))
        return;

    CLEAR_FLAG(op, FLAG_DIALOG_PARSED);
    if (!op->dialog_information)
        return;

    current = op->dialog_information->all_messages;
    while (current) {
        next = current->next;
        free(current->match);
        free(current->message);
        currep = current->replies;
        while (currep) {
            nextrep = currep->next;
            free(currep->reply);
            free(currep->message);
            currep = nextrep;
        }
        free(current);
        current = next;
    }

    currep = op->dialog_information->all_replies;
    while (currep) {
        nextrep = currep->next;
        free(currep->reply);
        free(currep->message);
        free(currep);
        currep = nextrep;
    }

    free(op->dialog_information);
    op->dialog_information = NULL;
}
