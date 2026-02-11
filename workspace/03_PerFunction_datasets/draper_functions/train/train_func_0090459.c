groupNameForArea(unsigned int area) const
    {
        QString groupName = QString::number(area);
        if (area == 0 || !config->hasGroup(groupName)) {
            groupName = QString::fromLocal8Bit(cache.value(area).name);
        }
        return groupName;
    }
