connectDatabase(QSqlDatabase &DB, const int line)
{
    if (!DB.isOpen()) {
        if (!DB.open()) {
            Utils::Log::addError("EpisodeBase", tkTr(Trans::Constants::UNABLE_TO_OPEN_DATABASE_1_ERROR_2)
                                 .arg(DB.connectionName()).arg(DB.lastError().text()),
                                 __FILE__, line);
            return false;
        }
    }
    return true;
}
