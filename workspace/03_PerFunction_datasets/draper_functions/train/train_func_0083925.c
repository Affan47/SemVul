iconLoader()
{
    Q_D(Part);

    if (!d->m_iconLoader) {
        Q_ASSERT(componentData().isValid());
        d->m_iconLoader = new KIconLoader( componentData() );
    }
    return d->m_iconLoader;
}
