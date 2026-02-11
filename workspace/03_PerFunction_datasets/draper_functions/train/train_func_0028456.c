non_blocking_receive (message_t *message_)
{
    int qid = fetch_message (message_);

    if (!qid) {
        ypollset_t::integer_t signals = pollset.check ();
        if (signals) {
            process_commands (signals);
            qid = fetch_message (message_);
        }
    }

    return qid;
}
