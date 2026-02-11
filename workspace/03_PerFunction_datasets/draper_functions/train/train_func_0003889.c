setModel(Templates::TemplatesModel *model)
{
    Q_ASSERT(model);
    if (!model)
        return;
    d->m_Model = model;
    d->createMapper();
}
