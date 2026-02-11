prettyColumnName( Column index )
{
    switch ( index )
    {
    case Filename:   return i18nc( "The name of the file this track is stored in", "Filename" );
    case Title:      return i18n( "Title" );
    case Artist:     return i18n( "Artist" );
    case AlbumArtist: return i18n( "Album Artist" );
    case Composer:   return i18n( "Composer" );
    case Year:       return i18n( "Year" );
    case Album:      return i18n( "Album" );
    case DiscNumber: return i18n( "Disc Number" );
    case TrackNumber: return i18nc( "The Track number for this item", "Track" );
    case Bpm:        return i18n( "BPM" );
    case Genre:      return i18n( "Genre" );
    case Comment:    return i18n( "Comment" );
    case Directory:  return i18nc( "The location on disc of this track", "Directory" );
    case Type:       return i18n( "Type" );
    case Length:     return i18n( "Length" );
    case Bitrate:    return i18n( "Bitrate" );
    case SampleRate: return i18n( "Sample Rate" );
    case Score:      return i18n( "Score" );
    case Rating:     return i18n( "Rating" );
    case PlayCount:  return i18n( "Play Count" );
    case LastPlayed: return i18nc( "Column name", "Last Played" );
    case Mood:       return i18n( "Mood" );
    case Filesize:   return i18n( "File Size" );
    default:         return "This is a bug.";
    }

}
