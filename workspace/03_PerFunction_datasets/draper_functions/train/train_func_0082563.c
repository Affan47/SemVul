clientRename (const QString & src, const QString & dest)
{
  return CommandPtr( new imapCommand( "RENAME",
                          QString( "\"" ) + KIMAP::encodeImapFolderName( src ) +
                          "\" \"" + KIMAP::encodeImapFolderName( dest ) + "\"" ) );
}
