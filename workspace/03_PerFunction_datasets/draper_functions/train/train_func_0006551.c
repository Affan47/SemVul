printGroups()
{
    for(int i = 0; i <= 1; ++i)
    {
        MultiOverlap mo_group(m_rootID, m_rootSeq);
        for(size_t j = 0; j < m_overlaps.size(); ++j)
        {
            const MOData& curr = m_overlaps[j];
            if(curr.partitionID == i)
                mo_group.add(curr);
        }
        std::cout << "MO GROUP " << i << "\n";
        mo_group.print();
    }
}
