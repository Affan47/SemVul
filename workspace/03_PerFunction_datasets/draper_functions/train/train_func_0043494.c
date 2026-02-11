matchItems(QHash<QString,KService::Ptr>& items1, const QHash<QString,KService::Ptr>& items2)
{
   foreach (const KService::Ptr &p, items1)
   {
       QString id = p->menuId();
       if (!items2.contains(id))
          items1.remove(id);
   }
}
