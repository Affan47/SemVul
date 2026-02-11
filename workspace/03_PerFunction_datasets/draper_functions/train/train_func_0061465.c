getSelected(size_t start, size_t end) const
{

    if (_textFields.empty()) return false;

    start = std::min(start, _count);
    end = std::min(end, _count);

    TextFields::const_iterator field = _textFields.begin();

    size_t totalChars = field->first->getSelected().size();
    size_t fieldStartIndex = 0;

    for (size_t i = start; i < end; ++i) {


        while (totalChars <= i) {
            fieldStartIndex = totalChars;
            ++field;
            if (field == _textFields.end()) return false;

            const boost::dynamic_bitset<>& sel = field->first->getSelected();
            totalChars += sel.size();
            continue;
        }

        if (field->first->getSelected().test(i - fieldStartIndex)) return true;
    }

    return false;
}
