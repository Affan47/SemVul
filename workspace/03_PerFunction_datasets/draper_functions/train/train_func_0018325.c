getMainFormCollection()
    {

        QString absDirPath = episodeBase()->getGenericFormFile();
        if (absDirPath.isEmpty()) {

            LOG_ERROR_FOR(q, "No patient central form defined");
            Q_ASSERT(false);
            return false;
        }

        LOG_FOR(q, "Loading patient form: " + absDirPath);

        if (!loadFormCollection(absDirPath, CompleteForms)) {
            LOG_ERROR_FOR(q, "Unable to load main form: " + absDirPath);
            return false;
        }
        const FormCollection &main = extractFormCollectionFrom(_centralFormCollection, CompleteForms, absDirPath);
        if (main.isNull()) {
            LOG_ERROR_FOR(q, QString("Unable to load main form: %1. No collection loaded").arg(absDirPath));
            return false;
        }


        if (main.emptyRootForms().count() > 0) {
            main.emptyRootForms().at(0)->reader()->loadPmhCategories(absDirPath);
            return true;
        }
        LOG_FOR(q, "Patient form loaded : " + absDirPath);
        return false;
    }
