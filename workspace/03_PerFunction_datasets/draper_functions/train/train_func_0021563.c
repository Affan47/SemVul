profilingReport(const char *what, const PluginSpec *spec )
{
    if (!m_profileTimer.isNull()) {
        const int absoluteElapsedMS = m_profileTimer->elapsed();
        const int elapsedMS = absoluteElapsedMS - m_profileElapsedMS;
        m_profileElapsedMS = absoluteElapsedMS;
        if (spec) {
            qDebug("%-22s %-22s %8dms (%8dms)", what, qPrintable(spec->name()), absoluteElapsedMS, elapsedMS);
        } else {
            qDebug("%-45s %8dms (%8dms)", what, absoluteElapsedMS, elapsedMS);
        }
    }
}
