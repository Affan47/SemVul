InitWebActionMaps() {
#ifdef LOCO_WEB_ACTION_MAP
#error "LOCO_WEB_ACTION_MAP already defined"
#endif
#define LOCO_WEB_ACTION_MAP( A ) \
    webActionToStringG[  QWebPage::A ] = #A; \
    stringToWebActionG[ #A ] = QWebPage::A

    LOCO_WEB_ACTION_MAP( NoWebAction );LOCO_WEB_ACTION_MAP( OpenLink );
    LOCO_WEB_ACTION_MAP( OpenLinkInNewWindow );LOCO_WEB_ACTION_MAP( OpenFrameInNewWindow );
    LOCO_WEB_ACTION_MAP( DownloadLinkToDisk );LOCO_WEB_ACTION_MAP( CopyLinkToClipboard );
    LOCO_WEB_ACTION_MAP( OpenImageInNewWindow );LOCO_WEB_ACTION_MAP( DownloadImageToDisk );
    LOCO_WEB_ACTION_MAP( CopyImageToClipboard );LOCO_WEB_ACTION_MAP( Back );
    LOCO_WEB_ACTION_MAP( Forward );LOCO_WEB_ACTION_MAP( Stop );
    LOCO_WEB_ACTION_MAP( Reload );LOCO_WEB_ACTION_MAP( OpenLink );
    LOCO_WEB_ACTION_MAP( Paste );LOCO_WEB_ACTION_MAP( Copy );
    LOCO_WEB_ACTION_MAP( Cut );LOCO_WEB_ACTION_MAP( Copy );
    LOCO_WEB_ACTION_MAP( Undo );LOCO_WEB_ACTION_MAP( Redo );
    LOCO_WEB_ACTION_MAP( MoveToNextChar );LOCO_WEB_ACTION_MAP( MoveToPreviousChar );
    LOCO_WEB_ACTION_MAP( MoveToNextWord );LOCO_WEB_ACTION_MAP( MoveToPreviousWord );
    LOCO_WEB_ACTION_MAP( MoveToNextLine );LOCO_WEB_ACTION_MAP( MoveToPreviousLine );
    LOCO_WEB_ACTION_MAP( MoveToStartOfLine );LOCO_WEB_ACTION_MAP( MoveToEndOfLine );
    LOCO_WEB_ACTION_MAP( MoveToStartOfBlock );LOCO_WEB_ACTION_MAP( MoveToEndOfBlock );
    LOCO_WEB_ACTION_MAP( MoveToStartOfDocument );LOCO_WEB_ACTION_MAP( MoveToEndOfDocument );
    LOCO_WEB_ACTION_MAP( SelectNextChar );LOCO_WEB_ACTION_MAP( SelectPreviousChar );
    LOCO_WEB_ACTION_MAP( SelectNextWord );LOCO_WEB_ACTION_MAP( SelectPreviousWord );
    LOCO_WEB_ACTION_MAP( SelectNextLine );LOCO_WEB_ACTION_MAP( SelectPreviousLine );
    LOCO_WEB_ACTION_MAP( SelectStartOfLine );LOCO_WEB_ACTION_MAP( SelectEndOfLine );
    LOCO_WEB_ACTION_MAP( SelectStartOfBlock );LOCO_WEB_ACTION_MAP( SelectEndOfBlock );
    LOCO_WEB_ACTION_MAP( SelectStartOfDocument );LOCO_WEB_ACTION_MAP( SelectEndOfDocument );
    LOCO_WEB_ACTION_MAP( DeleteStartOfWord );LOCO_WEB_ACTION_MAP( DeleteEndOfWord );
    LOCO_WEB_ACTION_MAP( SetTextDirectionDefault );LOCO_WEB_ACTION_MAP( SelectEndOfLine );
    LOCO_WEB_ACTION_MAP( SelectStartOfBlock );LOCO_WEB_ACTION_MAP( SetTextDirectionLeftToRight );
    LOCO_WEB_ACTION_MAP( SetTextDirectionRightToLeft );LOCO_WEB_ACTION_MAP( ToggleBold );
    LOCO_WEB_ACTION_MAP( ToggleItalic );LOCO_WEB_ACTION_MAP( ToggleUnderline );
    LOCO_WEB_ACTION_MAP( InspectElement );LOCO_WEB_ACTION_MAP( InsertParagraphSeparator );
    LOCO_WEB_ACTION_MAP( InsertLineSeparator );LOCO_WEB_ACTION_MAP( SelectAll );
    LOCO_WEB_ACTION_MAP( ReloadAndBypassCache );LOCO_WEB_ACTION_MAP( PasteAndMatchStyle );
    LOCO_WEB_ACTION_MAP( RemoveFormat );LOCO_WEB_ACTION_MAP( ToggleStrikethrough );
    LOCO_WEB_ACTION_MAP( ToggleSubscript );LOCO_WEB_ACTION_MAP( ToggleSuperscript );
    LOCO_WEB_ACTION_MAP( InsertUnorderedList );LOCO_WEB_ACTION_MAP( InsertOrderedList );
    LOCO_WEB_ACTION_MAP( Indent );LOCO_WEB_ACTION_MAP( Outdent );
    LOCO_WEB_ACTION_MAP( AlignCenter );LOCO_WEB_ACTION_MAP( AlignJustified );
    LOCO_WEB_ACTION_MAP( AlignLeft );LOCO_WEB_ACTION_MAP( AlignRight );
    LOCO_WEB_ACTION_MAP( StopScheduledPageRefresh );LOCO_WEB_ACTION_MAP( CopyImageUrlToClipboard );
    LOCO_WEB_ACTION_MAP( WebActionCount );
}
