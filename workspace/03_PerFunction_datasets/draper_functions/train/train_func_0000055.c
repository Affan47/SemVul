excludeItems(QHash<QString,KService::Ptr>& items1, const QHash<QString,KService::Ptr>& items2)
{
   foreach (const KService::Ptr &p, items2)
       items1.remove(p->menuId());
}
