selectColumn(const std::string& memberName, const std::string& title)
    {
        _titles.resize(_titles.size() + 1);
        _titles.back()._memberName = memberName;
        _titles.back()._title = title;
        _collectTitles = false;
    }
