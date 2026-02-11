pageReferrer() const
{
   KUrl referrerURL = KUrl( d->m_pageReferrer );
   if (referrerURL.isValid())
   {
      QString protocol = referrerURL.protocol();

      if ((protocol == "http") ||
         ((protocol == "https") && (url().protocol() == "https")))
      {
          referrerURL.setRef(QString());
          referrerURL.setUser(QString());
          referrerURL.setPass(QString());
          return referrerURL.url();
      }
   }

   return QString();
}
