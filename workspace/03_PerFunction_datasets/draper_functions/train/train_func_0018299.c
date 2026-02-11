_k_updateFstabMountPointsCache()
{
    if (globalFstabCache->m_fstabCacheValid)
        return;

    globalFstabCache->m_fstabCache.clear();

#ifdef HAVE_SETMNTENT

    FILE *fstab;
    if ((fstab = setmntent(FSTAB, "r")) == 0) {
        return;
    }

    struct mntent *fe;
    while ((fe = getmntent(fstab)) != 0) {
        if (_k_isFstabNetworkFileSystem(fe->mnt_type, fe->mnt_fsname)) {
            const QString device = QFile::decodeName(fe->mnt_fsname);
            const QString mountpoint = QFile::decodeName(fe->mnt_dir);

            globalFstabCache->m_fstabCache.insert(device, mountpoint);
        }
    }

    endmntent(fstab);

#else

    QFile fstab(FSTAB);
    if (!fstab.open(QIODevice::ReadOnly)) {
        return;
    }

    QTextStream stream(&fstab);
    QString line;

    while (!stream.atEnd()) {
        line = stream.readLine().simplified();
        if (line.isEmpty() || line.startsWith('#')) {
            continue;
        }


        const QStringList items = line.split(' ');

#ifdef Q_OS_SOLARIS
        if (items.count() < 5) {
            continue;
        }
#else
        if (items.count() < 4) {
            continue;
        }
#endif

        if (_k_isFstabNetworkFileSystem(items.at(2), items.at(0))) {
            const QString device = items.at(0);
            const QString mountpoint = items.at(1);

            globalFstabCache->m_fstabCache.insert(device, mountpoint);
        }
    }

    fstab.close();
#endif
    globalFstabCache->m_fstabCacheValid = true;
}
