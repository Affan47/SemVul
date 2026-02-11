print(int default_padding, int max_overhang)
{
    std::sort(m_overlaps.begin(), m_overlaps.end(), MOData::sortOffset);
    std::cout << "\nDrawing overlaps for read " << m_rootID << "\n";
    int root_len = int(m_rootSeq.size());


    printRow(default_padding, max_overhang, root_len, 0, root_len, 0, 0.0f, m_rootSeq, m_rootID);

    for(size_t i = 0; i < m_overlaps.size(); ++i)
    {
        const MOData& curr = m_overlaps[i];
        int overlap_len = curr.ovr.match.getMaxOverlapLength();
        int nd = curr.ovr.match.countDifferences(m_rootSeq, curr.seq);
        double score = static_cast<double>(nd) / overlap_len;
        printRow(default_padding, max_overhang, root_len,
                 curr.offset, overlap_len, nd,
                 score, curr.seq, curr.ovr.id[1].c_str());
    }
}
