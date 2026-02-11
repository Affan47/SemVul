hasContext(KIconLoader::Context context) const
{
    foreach(KIconThemeDir *dir, d->mDirs) {
        if ((context == KIconLoader::Any) || (context == dir->context())) {
            return true;
        }
    }
    return false;
}
