loadMenu(const QString &fileName)
{
   m_defaultMergeDirs.clear();

   if (!fileName.endsWith(QLatin1String(".menu")))
      return;

   pushDocInfo(fileName);
   m_defaultMergeDirs << m_docInfo.baseName+"-merged/";
   m_doc = loadDoc();
   popDocInfo();

   if (m_doc.isNull())
   {
      if (m_docInfo.path.isEmpty())
         kError(7021) << fileName << " not found in " << m_allDirectories << endl;
      else
         kWarning(7021) << "Load error (" << m_docInfo.path << ")";
      return;
   }

   QDomElement e = m_doc.documentElement();
   QString name;
   mergeMenus(e, name);
}
