addAlgoAt(std::vector<AlgorithmEnum* >& a, AlgorithmEnum& algo, int32_t index) {
    if (index >= maxNoOfAlgos)
        return -1;

    int size = (int)a.size();

    if (!algo.isValid())
        return -1;


    if (index >= size) {
        a.push_back(&algo);
        return maxNoOfAlgos - (int)a.size();
    }
    std::vector<AlgorithmEnum* >::iterator b = a.begin();
    std::vector<AlgorithmEnum* >::iterator e = a.end();

    for (int i = 0; b != e; ++b) {
        if (i == index) {
            a.insert(b, &algo);
            break;
        }
        i++;
    }
    return (maxNoOfAlgos - (int)a.size());
}
