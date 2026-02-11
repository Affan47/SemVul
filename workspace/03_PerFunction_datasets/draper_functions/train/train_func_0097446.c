ComputeTotalLatencies()
{
    std::vector<jack_int_t> sorted;
    std::vector<jack_int_t>::iterator it;
    std::vector<jack_int_t>::reverse_iterator rit;

    fGraphManager->TopologicalSort(sorted);


    for (it = sorted.begin(); it != sorted.end(); it++) {
        NotifyClient(*it, kLatencyCallback, true, "", 0, 0);
    }


    for (rit = sorted.rbegin(); rit != sorted.rend(); rit++) {
        NotifyClient(*rit, kLatencyCallback, true, "", 1, 0);
    }

    return 0;
}
