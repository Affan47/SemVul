equals( const KUrl &_u, const EqualsOptions& options ) const
{
  if ( !isValid() || !_u.isValid() )
    return false;

  if ( options & CompareWithoutTrailingSlash || options & CompareWithoutFragment )
  {
    QString path1 = path((options & CompareWithoutTrailingSlash) ? RemoveTrailingSlash : LeaveTrailingSlash);
    QString path2 = _u.path((options & CompareWithoutTrailingSlash) ? RemoveTrailingSlash : LeaveTrailingSlash);

    if (options & AllowEmptyPath) {
        if (path1 == QLatin1String("/"))
            path1.clear();
        if (path2 == QLatin1String("/"))
            path2.clear();
    }

#ifdef Q_WS_WIN
    const bool bLocal1 = isLocalFile();
    const bool bLocal2 = _u.isLocalFile();
    if ( !bLocal1 && bLocal2 || bLocal1 && !bLocal2 )
      return false;

    if ( bLocal1 && bLocal2 && 0 != QString::compare( path1, path2, Qt::CaseInsensitive ) )
      return false;
#endif
    if ( path1 != path2 )
      return false;

    if ( scheme() == _u.scheme() &&
         authority() == _u.authority() &&
         encodedQuery() == _u.encodedQuery() &&
         (fragment() == _u.fragment() || options & CompareWithoutFragment )    )
      return true;

    return false;
  }

  return ( *this == _u );
}
