update_fuzzy_pinyins()
{
    bool enabled = m_config.get(QUANPIN_FUZZY_ENABLED, false);
    AQuanpinSchemePolicy::instance().setFuzzyForwarding(enabled);
    AShuangpinSchemePolicy::instance().setFuzzyForwarding(enabled);
    if (!enabled)
        return;
    vector<string> fuzzy_pinyins;
    fuzzy_pinyins = m_config.get(QUANPIN_FUZZY_PINYINS, fuzzy_pinyins);
    AQuanpinSchemePolicy::instance().setFuzzyPinyinPairs(parse_pairs(fuzzy_pinyins));
    AShuangpinSchemePolicy::instance().setFuzzyPinyinPairs(parse_pairs(fuzzy_pinyins));
}
