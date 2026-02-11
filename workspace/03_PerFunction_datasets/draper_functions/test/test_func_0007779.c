newCloud(const WordList & words)
{

    qDeleteAll(m_wordItems);
    m_wordItems.clear();
    int minCount = 0;
    int maxCount = 0;
    foreach (const Word & word, words) {
        if (word.count < minCount || !minCount)
            minCount = word.count;
        if (word.count > maxCount || !maxCount)
            maxCount = word.count;
    }


    foreach (const Word & word, words) {
#if 1
        double rot = ((qrand() % 4) == 1) ? 90 : 0.0;
#else
        double rot = qrand() % 360;
#endif
        WordItem * wordItem = new WordItem(word, m_appearance.font, rot, minCount, maxCount);
        wordItem->show();

        m_wordItems.append(wordItem);
        if (m_scene)
            m_scene->addItem(wordItem);
    }


    m_dirty = true;
    process();
}
