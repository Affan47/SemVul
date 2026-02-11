getStaticText(std::vector<const SWF::TextRecord*>& to,
        size_t& numChars)
{
    _selectedText.clear();

    if (_def->extractStaticText(to, numChars)) {
        _selectedText.resize(numChars);
        return this;
    }

    return 0;
}
